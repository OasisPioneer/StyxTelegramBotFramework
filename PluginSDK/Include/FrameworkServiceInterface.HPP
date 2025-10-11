#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP

#include "LoggerInterface.HPP"
#include "TelegramDataStructure.HPP"

#include <string>
#include <optional>
#include <functional>

class FrameworkServiceInterface {
    public:
        virtual ~FrameworkServiceInterface() = default;
        virtual LoggerInterface* GetLogger() = 0;
        
        // 消息发送接口
        virtual bool SendMessage(const Telegram::ChatId& chat_id, const std::string& text,
                               std::optional<Telegram::InlineKeyboardMarkup> reply_markup = std::nullopt,
                               std::optional<std::int32_t> reply_to_message_id = std::nullopt) { return false; }
        
        virtual bool EditMessage(const Telegram::ChatId& chat_id, std::int32_t message_id,
                                const std::string& text,
                                std::optional<Telegram::InlineKeyboardMarkup> reply_markup = std::nullopt) { return false; }
        
        virtual bool DeleteMessage(const Telegram::ChatId& chat_id, std::int32_t message_id) { return false; }
        
        virtual bool AnswerCallbackQuery(const std::string& callback_query_id,
                                        const std::optional<std::string>& text = std::nullopt,
                                        bool show_alert = false) { return false; }
        
        virtual bool SendChatAction(const Telegram::ChatId& chat_id, const std::string& action) { return false; }
        
        // 注册命令处理器
        using CommandHandler = std::function<void(const Telegram::Message&)>;
        virtual void RegisterCommand(const std::string& command, CommandHandler handler) {}
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP