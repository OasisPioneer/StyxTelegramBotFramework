#ifndef STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP

#include "TelegramDataStructure.HPP"

#include <string>
#include <chrono>
#include <optional>

#include <boost/json/object.hpp>
#include <boost/system/error_code.hpp>

class TelegramHTTPClientIMPL;

/**
 * @brief
 *   @if LANG_CN Telegram Bot API 的 HTTP 客户端封装，提供同步请求能力。
 *   @endif
 *   @if LANG_EN HTTP client wrapper for the Telegram Bot API providing synchronous request capability.
 *   @endif
 */
class TelegramHTTPClient {
    public:
        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化底层实现并准备网络资源。
         *   @endif
         *   @if LANG_EN Constructor that initializes the underlying implementation and prepares network resources.
         *   @endif
         */
        TelegramHTTPClient();

        /**
         * @brief
         *   @if LANG_CN 析构函数，释放内部实现所持资源。
         *   @endif
         *   @if LANG_EN Destructor that releases resources held by the internal implementation.
         *   @endif
         */
        ~TelegramHTTPClient();

        TelegramHTTPClient(const TelegramHTTPClient&) = delete;
        TelegramHTTPClient& operator=(const TelegramHTTPClient&) = delete;

        /**
         * @brief
         *   @if LANG_CN 执行 Telegram API 请求并返回响应字符串。
         *   @endif
         *   @if LANG_EN Executes a Telegram API request and returns the response string.
         *   @endif
         *
         * @param Token
         *   @if LANG_CN 机器人访问令牌。
         *   @endif
         *   @if LANG_EN Bot access token.
         *   @endif
         * @param Method
         *   @if LANG_CN 要调用的 API 方法名称。
         *   @endif
         *   @if LANG_EN Name of the API method to invoke.
         *   @endif
         * @param Params
         *   @if LANG_CN JSON 参数对象，将序列化为请求正文。
         *   @endif
         *   @if LANG_EN JSON parameter object serialized into the request body.
         *   @endif
         * @param OutPutResponse
         *   @if LANG_CN 输出参数，用于接收服务器返回的正文。
         *   @endif
         *   @if LANG_EN Output parameter receiving the response body.
         *   @endif
         * @param OutPutError
         *   @if LANG_CN 输出错误码，描述失败原因。
         *   @endif
         *   @if LANG_EN Output error code describing the failure reason.
         *   @endif
         * @param TimeOut
         *   @if LANG_CN 请求超时时间，默认 30 秒。
         *   @endif
         *   @if LANG_EN Request timeout duration, default 30 seconds.
         *   @endif
         *
         * @return
         *   @if LANG_CN 请求成功返回 `true`，否则为 `false`。
         *   @endif
         *   @if LANG_EN Returns `true` on success, otherwise `false`.
         *   @endif
         */
        bool PerformRequest(
            const std::string& Token,
            const std::string& Method,
            const boost::json::object& Params,
            std::string& OutPutResponse,
            boost::system::error_code& OutPutError,
            std::chrono::seconds TimeOut = std::chrono::seconds(30)
            );
    
    /**
     * @brief
     *   @if LANG_CN 发送文本消息。
     *   @endif
     *   @if LANG_EN Sends a text message.
     *   @endif
     */
    bool SendMessage(
        const std::string& Token,
        const Telegram::ChatId& ChatId,
        const std::string& Text,
        const std::optional<Telegram::InlineKeyboardMarkup>& ReplyMarkup = std::nullopt,
        const std::optional<std::int32_t>& ReplyToMessageId = std::nullopt,
        boost::system::error_code* OutPutError = nullptr
    );
    
    /**
     * @brief
     *   @if LANG_CN 编辑消息。
     *   @endif
     *   @if LANG_EN Edits a message.
     *   @endif
     */
    bool EditMessage(
        const std::string& Token,
        const Telegram::ChatId& ChatId,
        std::int32_t MessageId,
        const std::string& Text,
        const std::optional<Telegram::InlineKeyboardMarkup>& ReplyMarkup = std::nullopt,
        boost::system::error_code* OutPutError = nullptr
    );
    
    /**
     * @brief
     *   @if LANG_CN 删除消息。
     *   @endif
     *   @if LANG_EN Deletes a message.
     *   @endif
     */
    bool DeleteMessage(
        const std::string& Token,
        const Telegram::ChatId& ChatId,
        std::int32_t MessageId,
        boost::system::error_code* OutPutError = nullptr
    );
    
    /**
     * @brief
     *   @if LANG_CN 回答回调查询。
     *   @endif
     *   @if LANG_EN Answers a callback query.
     *   @endif
     */
    bool AnswerCallbackQuery(
        const std::string& Token,
        const std::string& CallbackQueryId,
        const std::optional<std::string>& Text = std::nullopt,
        bool ShowAlert = false,
        boost::system::error_code* OutPutError = nullptr
    );
    private:
        TelegramHTTPClientIMPL* IMPL_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP