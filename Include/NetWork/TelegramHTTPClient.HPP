#ifndef STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP

#include <string>
#include <chrono>

#include <boost/json/object.hpp>
#include <boost/system/error_code.hpp>

class TelegramHTTPClientIMPL;

class TelegramHTTPClient {
    public:
        TelegramHTTPClient();
        ~TelegramHTTPClient();

        TelegramHTTPClient(const TelegramHTTPClient&) = delete;
        TelegramHTTPClient& operator=(const TelegramHTTPClient&) = delete;

        bool PerformRequest(
            const std::string& Token,
            const std::string& Method,
            const boost::json::object& Params,
            std::string& OutPutResponse,
            boost::system::error_code& OutPutError,
            std::chrono::seconds TimeOut = std::chrono::seconds(30)
            );
    private:
        TelegramHTTPClientIMPL* IMPL_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TELEGRAMHTTPCLIENT_HPP