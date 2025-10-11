#include "MyFirstPlugin.HPP"
#include <sstream>

const char* MyFirstPlugin::Initialize(FrameworkServiceInterface* Service) {

    if (Service) {
        this->Service_ = Service;
        // 请替换为您的实际 Bot Token
        this->Token_ = "YOUR_BOT_TOKEN_HERE";
    }
    if (Service_ && Service_->GetLogger()) {
        Service_->GetLogger()->Info("MyFirstPlugin Initialized.");
    }
    return this->Token_.c_str();
}

const char *MyFirstPlugin::Token() const {
    return Token_.c_str();
}


void MyFirstPlugin::Enable() {
    if (Service_ && Service_->GetLogger()) {
        // 使用保存的服务指针来获取 Logger
        Service_->GetLogger()->Info("MyFirstPlugin Enabled!");
        // 你也可以在这里使用令牌
        Service_->GetLogger()->Info(("Token used: " + Token_).c_str());
    }
}

void MyFirstPlugin::Disable() {
    if (Service_ && Service_->GetLogger()) {
        Service_->GetLogger()->Info("MyFirstPlugin Disabled!");
    }
}

// 处理收到的消息
void MyFirstPlugin::OnMessage(const Telegram::Message& message) {
    if (!Service_) return;
    
    // 记录收到的消息
    if (Service_->GetLogger() && message.Text.has_value()) {
        std::stringstream log;
        log << "Received message: " << message.Text.value();
        Service_->GetLogger()->Info(log.str().c_str());
    }
    
    // 如果不是命令，回显消息
    if (message.Text.has_value() && !message.Text.value().empty() && 
        message.Text.value()[0] != '/') {
        
        // 发送回显消息
        std::string echo_text = "Echo: " + message.Text.value();
        Service_->SendMessage(message.ChatInfo.Id, echo_text, std::nullopt, message.MessageId);
    }
}

// 处理回调查询
void MyFirstPlugin::OnCallbackQuery(const Telegram::CallbackQuery& query) {
    if (!Service_) return;
    
    if (Service_->GetLogger()) {
        std::stringstream log;
        log << "Received callback query: " << query.Data.value_or("[no data]");
        Service_->GetLogger()->Info(log.str().c_str());
    }
    
    // 回答回调查询
    std::string answer_text = "You clicked: " + query.Data.value_or("unknown");
    Service_->AnswerCallbackQuery(query.Id, answer_text, false);
    
    // 编辑原消息
    if (query.MessageInfo.has_value()) {
        const auto& msg = query.MessageInfo.value();
        std::string new_text = "Button clicked! Data: " + query.Data.value_or("none");
        Service_->EditMessage(msg.ChatInfo.Id, msg.MessageId, new_text);
    }
}

// 处理命令
void MyFirstPlugin::OnCommand(const std::string& command, const Telegram::Message& message) {
    if (!Service_) return;
    
    if (command == "start") {
        std::string welcome_text = "Welcome to MyFirstPlugin!\n\n"
                                  "Available commands:\n"
                                  "/start - Show this message\n"
                                  "/help - Get help\n"
                                  "/keyboard - Show inline keyboard\n"
                                  "/echo <text> - Echo your text";
        Service_->SendMessage(message.ChatInfo.Id, welcome_text);
        
    } else if (command == "help") {
        std::string help_text = "This is a simple demo plugin.\n"
                               "Send me any text and I'll echo it back!";
        Service_->SendMessage(message.ChatInfo.Id, help_text);
        
    } else if (command == "keyboard") {
        // 创建内联键盘
        Telegram::InlineKeyboardMarkup markup;
        std::vector<Telegram::InlineKeyboardButton> row1, row2;
        
        Telegram::InlineKeyboardButton btn1;
        btn1.Text = "Button 1";
        btn1.CallbackData = "btn1_clicked";
        row1.push_back(btn1);
        
        Telegram::InlineKeyboardButton btn2;
        btn2.Text = "Button 2";
        btn2.CallbackData = "btn2_clicked";
        row1.push_back(btn2);
        
        Telegram::InlineKeyboardButton btn3;
        btn3.Text = "Visit Telegram";
        btn3.Url = "https://telegram.org";
        row2.push_back(btn3);
        
        markup.InlineKeyboard.push_back(row1);
        markup.InlineKeyboard.push_back(row2);
        
        Service_->SendMessage(message.ChatInfo.Id, "Here's an inline keyboard:", markup);
        
    } else if (command == "echo") {
        // 提取命令后的文本
        std::string text;
        if (message.Text.has_value()) {
            size_t space_pos = message.Text.value().find(' ');
            if (space_pos != std::string::npos) {
                text = message.Text.value().substr(space_pos + 1);
            }
        }
        
        if (text.empty()) {
            Service_->SendMessage(message.ChatInfo.Id, "Usage: /echo <your text>");
        } else {
            Service_->SendMessage(message.ChatInfo.Id, "Echo: " + text);
        }
    }
}

// 获取支持的命令列表
std::vector<std::string> MyFirstPlugin::GetSupportedCommands() const {
    return {"start", "help", "keyboard", "echo"};
}

extern "C" PluginInterface* CreatePlugin() {
    return new MyFirstPlugin();
}