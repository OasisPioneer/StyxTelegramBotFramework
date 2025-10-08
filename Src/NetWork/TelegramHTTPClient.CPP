#include "NetWork/TelegramHTTPClient.HPP"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/json/serialize.hpp>

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
        boost::beast::flat_buffer Buffer;
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