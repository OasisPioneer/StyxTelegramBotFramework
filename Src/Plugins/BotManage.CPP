#include "Plugins/BotManage.HPP"
#include "Core/System/LogCollector.HPP"

#include <chrono>

#include <boost/json.hpp>

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

void BotManage::BotLoop(const std::string& Token) {
    LOG_INFO(">>>>>> BotLoop thread started for a token! <<<<<<"); // <--- 添加这句
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

        LOG_INFO(("Received data for token " + Token.substr(0, 10) + ": " + ResponseString).c_str());

        try {
            auto data = boost::json::parse(ResponseString).as_object();
            if (data.contains("result") && data.at("result").is_array()) {
                const auto& results = data.at("result").as_array();
                if (!results.empty()) {
                    LastUpdateID = results.back().as_object().at("update_id").as_int64();
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR(("Failed to parse update_id from response: " + std::string(e.what())).c_str());
        }
    }
    LOG_INFO(("Bot loop for token " + Token.substr(0, 10) + " has exited.").c_str());
}

BotManage::~BotManage() {
    StopAll();
}