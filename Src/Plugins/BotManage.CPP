#include "Plugins/BotManage.HPP"
#include "Core/System/LogCollector.HPP"

#include <chrono>

#include <boost/json.hpp>
#include <unordered_map>

BotManage::BotManage(TelegramHTTPClient *Client) : HTTPClient_(Client) {}

void BotManage::RegisterBot(std::shared_ptr<PluginInterface> Plugin) {

    std::string Token = Plugin->Token();
    if (Token.empty()) {
        LOG_WARN("Plugin has an empty token. Cannot register bot.");
        return;
    }

    std::lock_guard<std::mutex> Lock(BotMutex_);
    if (Bots_.find(Token) == Bots_.end()) {
        LOG_INFO(("Registering bot for plugin: " + std::string(Plugin->Name())).c_str());
        auto& Instance = Bots_[Token];
        Instance.Plugin = Plugin;
        
        // 为插件设置 HTTP 客户端（如果插件使用了 FrameworkServices）
        // 注意：这需要在 PluginManage 中保存服务实例并提供访问方法
        
        // 启动该 Bot 的工作线程
        Instance.Worker = std::thread(&BotManage::BotLoop, this, Token);
    }
}

void BotManage::StopAll() {
   LOG_INFO("Stopping all bots...");
    std::unique_lock<std::mutex> Lock(BotMutex_);
    for (auto& Pair : Bots_) {
        Pair.second.Running = false;
    }
    Lock.unlock(); // 解锁以允许 BotLoop 线程访问 map 并退出

    for (auto& Pair : Bots_) {
        if (Pair.second.Worker.joinable()) {
            Pair.second.Worker.join();
        }
    }
    Bots_.clear();
    LOG_INFO("All bots stopped.");
}

// 解析 Update 对象的辅助函数
static Telegram::Update ParseUpdate(const boost::json::object& update_json) {
    Telegram::Update update;
    
    // 解析 update_id
    if (update_json.contains("update_id")) {
        update.UpdateId = static_cast<std::int32_t>(update_json.at("update_id").as_int64());
    }
    
    // 解析 message
    if (update_json.contains("message") && update_json.at("message").is_object()) {
        const auto& msg_obj = update_json.at("message").as_object();
        Telegram::Message message;
        
        // 解析基本字段
        if (msg_obj.contains("message_id")) {
            message.MessageId = static_cast<std::int32_t>(msg_obj.at("message_id").as_int64());
        }
        
        if (msg_obj.contains("text")) {
            message.Text = msg_obj.at("text").as_string().c_str();
        }
        
        // 解析 chat
        if (msg_obj.contains("chat") && msg_obj.at("chat").is_object()) {
            const auto& chat_obj = msg_obj.at("chat").as_object();
            message.ChatInfo.Id = chat_obj.at("id").as_int64();
            
            if (chat_obj.contains("type")) {
                message.ChatInfo.Type = chat_obj.at("type").as_string().c_str();
            }
            
            if (chat_obj.contains("title")) {
                message.ChatInfo.Title = chat_obj.at("title").as_string().c_str();
            }
        }
        
        // 解析 from
        if (msg_obj.contains("from") && msg_obj.at("from").is_object()) {
            const auto& from_obj = msg_obj.at("from").as_object();
            Telegram::User from_user;
            from_user.Id = from_obj.at("id").as_int64();
            from_user.IsBot = from_obj.contains("is_bot") ? from_obj.at("is_bot").as_bool() : false;
            from_user.FirstName = from_obj.at("first_name").as_string().c_str();
            
            if (from_obj.contains("username")) {
                from_user.Username = from_obj.at("username").as_string().c_str();
            }
            
            message.From = from_user;
        }
        
        update.MessageInfo = message;
    }
    
    // 解析 callback_query
    if (update_json.contains("callback_query") && update_json.at("callback_query").is_object()) {
        const auto& query_obj = update_json.at("callback_query").as_object();
        Telegram::CallbackQuery query;
        
        if (query_obj.contains("id")) {
            query.Id = query_obj.at("id").as_string().c_str();
        }
        
        if (query_obj.contains("data")) {
            query.Data = query_obj.at("data").as_string().c_str();
        }
        
        // 解析 from
        if (query_obj.contains("from") && query_obj.at("from").is_object()) {
            const auto& from_obj = query_obj.at("from").as_object();
            query.FromUser.Id = from_obj.at("id").as_int64();
            query.FromUser.IsBot = from_obj.contains("is_bot") ? from_obj.at("is_bot").as_bool() : false;
            query.FromUser.FirstName = from_obj.at("first_name").as_string().c_str();
        }
        
        // 解析 message
        if (query_obj.contains("message") && query_obj.at("message").is_object()) {
            // 简化解析，只获取必要字段
            const auto& msg_obj = query_obj.at("message").as_object();
            Telegram::Message message;
            
            if (msg_obj.contains("message_id")) {
                message.MessageId = static_cast<std::int32_t>(msg_obj.at("message_id").as_int64());
            }
            
            if (msg_obj.contains("chat") && msg_obj.at("chat").is_object()) {
                const auto& chat_obj = msg_obj.at("chat").as_object();
                message.ChatInfo.Id = chat_obj.at("id").as_int64();
            }
            
            query.MessageInfo = message;
        }
        
        update.CallbackQueryInfo = query;
    }
    
    return update;
}

void BotManage::BotLoop(const std::string& Token) {
    LOG_INFO(">>>>>> BotLoop thread started for a token! <<<<<<");
    long long LastUpdateID = 0;

    while (true) {
        {
            std::lock_guard<std::mutex> Lock(BotMutex_);
            auto it = Bots_.find(Token);
            if (it == Bots_.end() || !it->second.Running) {
                break;
            }
        }

        boost::json::object Params;
        Params["offset"] = LastUpdateID + 1;
        Params["timeout"] = 60;

        std::string ResponseString;
        boost::system::error_code ErrorCode;

        LOG_INFO(("Fetching updates for token: " + Token.substr(0, 10) + "...").c_str());

        // 使用比长轮询时间稍长的超时
        bool Success = HTTPClient_->PerformRequest(Token, "getUpdates", Params, ResponseString, ErrorCode, std::chrono::seconds(70 ));

        if (!Success) {
            LOG_ERROR(("getUpdates failed: " + ErrorCode.message()).c_str());
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }

        if (ResponseString.empty()) {
            LOG_INFO("getUpdates timed out (normal for long-polling), continuing...");
            continue;
        }

        LOG_INFO(("Received data for token " + Token.substr(0, 10) + ": " + ResponseString.substr(0, 100) + "...").c_str());

        try {
            auto data = boost::json::parse(ResponseString).as_object();
            if (data.contains("result") && data.at("result").is_array()) {
                const auto& results = data.at("result").as_array();
                
                // 处理每个更新
                for (const auto& result_val : results) {
                    if (result_val.is_object()) {
                        const auto& update_obj = result_val.as_object();
                        
                        // 解析 Update 对象
                        Telegram::Update update = ParseUpdate(update_obj);
                        
                        // 更新 LastUpdateID
                        if (update.UpdateId > LastUpdateID) {
                            LastUpdateID = update.UpdateId;
                        }
                        
                        // 分发到插件
                        {
                            std::lock_guard<std::mutex> Lock(BotMutex_);
                            auto it = Bots_.find(Token);
                            if (it != Bots_.end() && it->second.Plugin) {
                                // 调用插件的事件处理方法
                                it->second.Plugin->OnUpdate(update);
                                
                                // 处理消息
                                if (update.MessageInfo.has_value()) {
                                    const auto& message = update.MessageInfo.value();
                                    it->second.Plugin->OnMessage(message);
                                    
                                    // 检查是否为命令
                                    if (message.Text.has_value() && !message.Text.value().empty() && 
                                        message.Text.value()[0] == '/') {
                                        // 提取命令
                                        std::string text = message.Text.value();
                                        size_t space_pos = text.find(' ');
                                        std::string command = (space_pos != std::string::npos) ? 
                                            text.substr(1, space_pos - 1) : text.substr(1);
                                        
                                        // 检查插件是否支持该命令
                                        auto supported_commands = it->second.Plugin->GetSupportedCommands();
                                        if (std::find(supported_commands.begin(), supported_commands.end(), command) != 
                                            supported_commands.end()) {
                                            it->second.Plugin->OnCommand(command, message);
                                        }
                                    }
                                }
                                
                                // 处理回调查询
                                if (update.CallbackQueryInfo.has_value()) {
                                    it->second.Plugin->OnCallbackQuery(update.CallbackQueryInfo.value());
                                }
                                
                                // 处理其他事件类型...
                                if (update.EditedMessage.has_value()) {
                                    it->second.Plugin->OnEditedMessage(update.EditedMessage.value());
                                }
                                
                                if (update.InlineQueryInfo.has_value()) {
                                    it->second.Plugin->OnInlineQuery(update.InlineQueryInfo.value());
                                }
                            }
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR(("Failed to parse updates: " + std::string(e.what())).c_str());
        }
    }
    LOG_INFO(("Bot loop for token " + Token.substr(0, 10) + " has exited.").c_str());
}

BotManage::~BotManage() {
    StopAll();
}