#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP

#include "FrameworkServiceInterface.HPP"
#include "FrameworkLogger.HPP"
#include "NetWork/TelegramHTTPClient.HPP"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief
 *   @if LANG_CN 框架服务入口，为插件提供日志等通用能力。
 *   @endif
 *   @if LANG_EN Entry point for framework services offering common capabilities such as logging to plugins.
 *   @endif
 */
class FrameworkServices : public FrameworkServiceInterface {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化框架日志器实例。
         *   @endif
         *   @if LANG_EN Constructor that initializes the framework logger instance.
         *   @endif
         */
        FrameworkServices(TelegramHTTPClient* http_client = nullptr, const std::string& token = "") 
            : Logger_(std::make_unique<FrameworkLogger>()), 
              http_client_(http_client), 
              token_(token) {}

        /**
         * @brief
         *   @if LANG_CN 返回日志接口指针供插件使用。
         *   @endif
         *   @if LANG_EN Returns the logger interface pointer for plugin usage.
         *   @endif
         *
         * @return
         *   @if LANG_CN `LoggerInterface` 指针，用于记录框架级日志。
         *   @endif
         *   @if LANG_EN Pointer to `LoggerInterface` enabling framework-level logging.
         *   @endif
         */
        LoggerInterface* GetLogger() override {
            return Logger_.get();
        }
        
        // 消息发送实现
        bool SendMessage(const Telegram::ChatId& chat_id, const std::string& text,
                        std::optional<Telegram::InlineKeyboardMarkup> reply_markup = std::nullopt,
                        std::optional<std::int32_t> reply_to_message_id = std::nullopt) override {
            if (!http_client_ || token_.empty()) {
                return false;
            }
            
            boost::system::error_code error;
            return http_client_->SendMessage(token_, chat_id, text, reply_markup, reply_to_message_id, &error);
        }
        
        bool EditMessage(const Telegram::ChatId& chat_id, std::int32_t message_id,
                        const std::string& text,
                        std::optional<Telegram::InlineKeyboardMarkup> reply_markup = std::nullopt) override {
            if (!http_client_ || token_.empty()) {
                return false;
            }
            
            boost::system::error_code error;
            return http_client_->EditMessage(token_, chat_id, message_id, text, reply_markup, &error);
        }
        
        bool DeleteMessage(const Telegram::ChatId& chat_id, std::int32_t message_id) override {
            if (!http_client_ || token_.empty()) {
                return false;
            }
            
            boost::system::error_code error;
            return http_client_->DeleteMessage(token_, chat_id, message_id, &error);
        }
        
        bool AnswerCallbackQuery(const std::string& callback_query_id,
                                const std::optional<std::string>& text = std::nullopt,
                                bool show_alert = false) override {
            if (!http_client_ || token_.empty()) {
                return false;
            }
            
            boost::system::error_code error;
            return http_client_->AnswerCallbackQuery(token_, callback_query_id, text, show_alert, &error);
        }
        
        bool SendChatAction(const Telegram::ChatId& chat_id, const std::string& action) override {
            if (!http_client_ || token_.empty()) {
                return false;
            }
            
            // 简化实现，使用 PerformRequest
            boost::json::object params;
            if (std::holds_alternative<std::int64_t>(chat_id)) {
                params["chat_id"] = std::get<std::int64_t>(chat_id);
            } else {
                params["chat_id"] = std::get<std::string>(chat_id);
            }
            params["action"] = action;
            
            std::string response;
            boost::system::error_code error;
            return http_client_->PerformRequest(token_, "sendChatAction", params, response, error);
        }
        
        void RegisterCommand(const std::string& command, CommandHandler handler) override {
            command_handlers_[command] = handler;
        }
        
        // 设置 HTTP 客户端和令牌
        void SetHttpClient(TelegramHTTPClient* client) { http_client_ = client; }
        void SetToken(const std::string& token) { token_ = token; }
        
        // 获取命令处理器
        CommandHandler GetCommandHandler(const std::string& command) const {
            auto it = command_handlers_.find(command);
            return (it != command_handlers_.end()) ? it->second : nullptr;
        }
        
    private:
        std::unique_ptr<FrameworkLogger> Logger_;
        TelegramHTTPClient* http_client_;
        std::string token_;
        std::unordered_map<std::string, CommandHandler> command_handlers_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP