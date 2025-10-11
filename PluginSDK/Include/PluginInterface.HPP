#ifndef STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP

#include "FrameworkServiceInterface.HPP"
#include "TelegramDataStructure.HPP"

#include <string>
#include <vector>

class PluginInterface {
    public:
        virtual ~PluginInterface() = default;
        virtual const char* Initialize(FrameworkServiceInterface* Service) = 0;

        virtual const char* Token() const = 0;

        virtual const char* Name() const = 0;
        virtual const char* Version() const = 0;
        virtual const char* Author() const = 0;
        virtual const char* Description() const = 0;

        virtual void Enable() = 0;
        virtual void Disable() = 0;
        
        // 事件处理接口（可选实现）
        virtual void OnUpdate(const Telegram::Update& update) {}
        virtual void OnMessage(const Telegram::Message& message) {}
        virtual void OnEditedMessage(const Telegram::Message& message) {}
        virtual void OnChannelPost(const Telegram::Message& message) {}
        virtual void OnEditedChannelPost(const Telegram::Message& message) {}
        virtual void OnInlineQuery(const Telegram::InlineQuery& query) {}
        virtual void OnChosenInlineResult(const Telegram::ChosenInlineResult& result) {}
        virtual void OnCallbackQuery(const Telegram::CallbackQuery& query) {}
        virtual void OnShippingQuery(const Telegram::ShippingQuery& query) {}
        virtual void OnPreCheckoutQuery(const Telegram::PreCheckoutQuery& query) {}
        virtual void OnPoll(const Telegram::Poll& poll) {}
        virtual void OnPollAnswer(const Telegram::PollAnswer& answer) {}
        virtual void OnChatMemberUpdated(const Telegram::ChatMemberUpdated& update) {}
        virtual void OnChatJoinRequest(const Telegram::ChatJoinRequest& request) {}
        
        // 命令处理接口
        virtual void OnCommand(const std::string& command, const Telegram::Message& message) {}
        
        // 获取插件支持的命令列表
        virtual std::vector<std::string> GetSupportedCommands() const { return {}; }
};

extern "C" {
    typedef PluginInterface* (*CreatePluginFunction)();
    PluginInterface* CreatePlugin();
}

#endif //STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP