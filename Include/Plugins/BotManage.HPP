#ifndef STYXTELEGRAMBOTFRAMEWORK_BOTMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_BOTMANAGE_HPP

#include "PluginInterface.HPP"
#include "NetWork/TelegramHTTPClient.HPP"

#include <string>
#include <memory>
#include <thread>
#include <map>
#include <atomic>
#include <mutex>

class BotManage {
    public:
        BotManage(TelegramHTTPClient* Client);
        ~BotManage();

        void RegisterBot(std::shared_ptr<PluginInterface> Plugin);
        void StopAll();
    private:
        struct BotInstance {
            std::shared_ptr<PluginInterface> Plugin;
            std::thread Worker;
            std::atomic<bool> Running{true};
            long long LastUpdateID = 0;
        };
        void BotLoop(const std::string& Token);

        TelegramHTTPClient* HTTPClient_;
        std::map<std::string, BotInstance> Bots_;
        std::mutex BotMutex_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_BOTMANAGE_HPP