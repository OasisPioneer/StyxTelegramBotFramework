#include "NetWork/TelegramHTTPClient.HPP"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/json.hpp>

class TelegramHTTPClientIMPL {
    public:
        TelegramHTTPClientIMPL() : SSL_ConText_(boost::asio::ssl::context::tlsv12_client) {
            SSL_ConText_.set_default_verify_paths();
            SSL_ConText_.set_verify_mode(boost::asio::ssl::verify_peer);
        }
        bool PerformRequest(
            const std::string& Token,
            const std::string& Method,
            const boost::json::object& Params,
            std::string& OutPutResponse,
            boost::system::error_code& OutPutError,
            std::chrono::seconds TimeOut
            );
private:
    boost::asio::io_context IO_ConText_;
    boost::asio::ssl::context SSL_ConText_;
    const std::string Host_ = "api.telegram.org";
    const std::string Port_ = "443";
};

bool TelegramHTTPClientIMPL::PerformRequest(
            const std::string& Token,const std::string& Method,const boost::json::object& Params,
            std::string& OutPutResponse,boost::system::error_code& OutPutError,std::chrono::seconds TimeOut)
{
    IO_ConText_.restart();
    try {
        boost::asio::ip::tcp::resolver Resolver(IO_ConText_);
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> Stream(IO_ConText_, SSL_ConText_);

        // SNI (Server Name Indication) 是 HTTPS 成功的关键
        if (!SSL_set_tlsext_host_name(Stream.native_handle(), Host_.c_str())) {
            OutPutError.assign(static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category());
            return false;
        }

        auto const Results = Resolver.resolve(Host_, Port_, OutPutError);
        if(OutPutError) return false;

        boost::asio::steady_timer Timer(IO_ConText_);
        Timer.expires_after(TimeOut);
        Timer.async_wait([&Stream](const boost::system::error_code& ec) {

            if (ec != boost::asio::error::operation_aborted) {
                Stream.next_layer().cancel();
            }
        });

        // 连接
        boost::asio::connect(Stream.next_layer(), Results.begin(), Results.end(), OutPutError);
        if(OutPutError) {
            Timer.cancel();
            return false;
        }

        // SSL 握手
        Stream.handshake(boost::asio::ssl::stream_base::client, OutPutError);
        if(OutPutError) {
            Timer.cancel();
            return false;
        }

        // 构建 HTTP 请求
        boost::beast::http::request<boost::beast::http::string_body> Request;
        Request.method(boost::beast::http::verb::post );
        Request.target("/bot" + Token + "/" + Method);
        Request.set(boost::beast::http::field::host, Host_ );
        Request.set(boost::beast::http::field::user_agent, PROJECT_NAME );
        Request.set(boost::beast::http::field::content_type, "application/json" );
        Request.body() = boost::json::serialize(Params);
        Request.prepare_payload();

        // 发送请求
        boost::beast::http::write(Stream, Request, OutPutError );
        if(OutPutError) return false;

        // 接收响应
        boost::beast::multi_buffer Buffer;
        boost::beast::http::response<boost::beast::http::string_body> Response;
        boost::beast::http::read(Stream, Buffer, Response, OutPutError );
        if(OutPutError) return false;

        // 优雅关闭
        Stream.shutdown(OutPutError);

        OutPutResponse = Response.body();
        return Response.result() == boost::beast::http::status::ok;

    } catch (const std::exception&) {
        // 捕获所有意料之外的异常
        OutPutError = boost::system::errc::make_error_code(boost::system::errc::interrupted);
        return false;
    }
}

TelegramHTTPClient::TelegramHTTPClient() {
    IMPL_ = new TelegramHTTPClientIMPL();
}

bool TelegramHTTPClient::PerformRequest(
    const std::string& Token,const std::string& Method,const boost::json::object& Params,
    std::string& OutPutResponse,boost::system::error_code& OutPutError,std::chrono::seconds TimeOut)
{
    return IMPL_->PerformRequest(Token, Method, Params, OutPutResponse, OutPutError, TimeOut);
}

TelegramHTTPClient::~TelegramHTTPClient() {
    delete IMPL_;
}

// 辅助函数：将 ChatId 转换为字符串
static std::string ChatIdToString(const Telegram::ChatId& chat_id) {
    if (std::holds_alternative<std::int64_t>(chat_id)) {
        return std::to_string(std::get<std::int64_t>(chat_id));
    } else {
        return std::get<std::string>(chat_id);
    }
}

// 辅助函数：将 InlineKeyboardMarkup 转换为 JSON
static boost::json::value InlineKeyboardToJson(const Telegram::InlineKeyboardMarkup& markup) {
    boost::json::array keyboard_array;
    for (const auto& row : markup.InlineKeyboard) {
        boost::json::array row_array;
        for (const auto& button : row) {
            boost::json::object button_obj;
            button_obj["text"] = button.Text;
            
            if (button.Url.has_value()) {
                button_obj["url"] = button.Url.value();
            }
            if (button.CallbackData.has_value()) {
                button_obj["callback_data"] = button.CallbackData.value();
            }
            if (button.SwitchInlineQuery.has_value()) {
                button_obj["switch_inline_query"] = button.SwitchInlineQuery.value();
            }
            if (button.SwitchInlineQueryCurrentChat.has_value()) {
                button_obj["switch_inline_query_current_chat"] = button.SwitchInlineQueryCurrentChat.value();
            }
            
            row_array.push_back(button_obj);
        }
        keyboard_array.push_back(row_array);
    }
    
    boost::json::object markup_obj;
    markup_obj["inline_keyboard"] = keyboard_array;
    return markup_obj;
}

bool TelegramHTTPClient::SendMessage(
    const std::string& Token,
    const Telegram::ChatId& ChatId,
    const std::string& Text,
    const std::optional<Telegram::InlineKeyboardMarkup>& ReplyMarkup,
    const std::optional<std::int32_t>& ReplyToMessageId,
    boost::system::error_code* OutPutError)
{
    boost::json::object params;
    params["chat_id"] = ChatIdToString(ChatId);
    params["text"] = Text;
    
    if (ReplyToMessageId.has_value()) {
        params["reply_to_message_id"] = ReplyToMessageId.value();
    }
    
    if (ReplyMarkup.has_value()) {
        params["reply_markup"] = boost::json::serialize(InlineKeyboardToJson(ReplyMarkup.value()));
    }
    
    std::string response;
    boost::system::error_code error;
    bool result = PerformRequest(Token, "sendMessage", params, response, error);
    
    if (OutPutError) {
        *OutPutError = error;
    }
    
    if (result) {
        try {
            auto parsed_value = boost::json::parse(response);
            auto json_response = parsed_value.as_object();
            return json_response.contains("ok") && json_response.at("ok").as_bool();
        } catch (...) {
            return false;
        }
    }
    
    return false;
}

bool TelegramHTTPClient::EditMessage(
    const std::string& Token,
    const Telegram::ChatId& ChatId,
    std::int32_t MessageId,
    const std::string& Text,
    const std::optional<Telegram::InlineKeyboardMarkup>& ReplyMarkup,
    boost::system::error_code* OutPutError)
{
    boost::json::object params;
    params["chat_id"] = ChatIdToString(ChatId);
    params["message_id"] = MessageId;
    params["text"] = Text;
    
    if (ReplyMarkup.has_value()) {
        params["reply_markup"] = boost::json::serialize(InlineKeyboardToJson(ReplyMarkup.value()));
    }
    
    std::string response;
    boost::system::error_code error;
    bool result = PerformRequest(Token, "editMessageText", params, response, error);
    
    if (OutPutError) {
        *OutPutError = error;
    }
    
    if (result) {
        try {
            auto parsed_value = boost::json::parse(response);
            auto json_response = parsed_value.as_object();
            return json_response.contains("ok") && json_response.at("ok").as_bool();
        } catch (...) {
            return false;
        }
    }
    
    return false;
}

bool TelegramHTTPClient::DeleteMessage(
    const std::string& Token,
    const Telegram::ChatId& ChatId,
    std::int32_t MessageId,
    boost::system::error_code* OutPutError)
{
    boost::json::object params;
    params["chat_id"] = ChatIdToString(ChatId);
    params["message_id"] = MessageId;
    
    std::string response;
    boost::system::error_code error;
    bool result = PerformRequest(Token, "deleteMessage", params, response, error);
    
    if (OutPutError) {
        *OutPutError = error;
    }
    
    if (result) {
        try {
            auto parsed_value = boost::json::parse(response);
            auto json_response = parsed_value.as_object();
            return json_response.contains("ok") && json_response.at("ok").as_bool();
        } catch (...) {
            return false;
        }
    }
    
    return false;
}

bool TelegramHTTPClient::AnswerCallbackQuery(
    const std::string& Token,
    const std::string& CallbackQueryId,
    const std::optional<std::string>& Text,
    bool ShowAlert,
    boost::system::error_code* OutPutError)
{
    boost::json::object params;
    params["callback_query_id"] = CallbackQueryId;
    
    if (Text.has_value()) {
        params["text"] = Text.value();
    }
    
    if (ShowAlert) {
        params["show_alert"] = true;
    }
    
    std::string response;
    boost::system::error_code error;
    bool result = PerformRequest(Token, "answerCallbackQuery", params, response, error);
    
    if (OutPutError) {
        *OutPutError = error;
    }
    
    if (result) {
        try {
            auto parsed_value = boost::json::parse(response);
            auto json_response = parsed_value.as_object();
            return json_response.contains("ok") && json_response.at("ok").as_bool();
        } catch (...) {
            return false;
        }
    }
    
    return false;
}