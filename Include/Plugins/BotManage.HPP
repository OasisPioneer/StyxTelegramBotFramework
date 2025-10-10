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

/**
 * @brief
 *   @if LANG_CN 机器人管理器，负责注册插件并驱动其更新循环。
 *   @endif
 *   @if LANG_EN Bot manager responsible for registering plugins and driving their update loops.
 *   @endif
 */
class BotManage {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，接受 Telegram HTTP 客户端指针以发送网络请求。
         *   @endif
         *   @if LANG_EN Constructor that accepts a Telegram HTTP client pointer for network requests.
         *   @endif
         */
        BotManage(TelegramHTTPClient* Client);

        /**
         * @brief
         *   @if LANG_CN 析构函数，自动停止所有正在运行的机器人任务。
         *   @endif
         *   @if LANG_EN Destructor that automatically stops all running bot tasks.
         *   @endif
         */
        ~BotManage();

        /**
         * @brief
         *   @if LANG_CN 注册插件实例并启动其轮询线程。
         *   @endif
         *   @if LANG_EN Registers a plugin instance and starts its polling thread.
         *   @endif
         *
         * @param Plugin
         *   @if LANG_CN 具有 Telegram Token 的插件实例。
         *   @endif
         *   @if LANG_EN Plugin instance that holds a Telegram token.
         *   @endif
         */
        void RegisterBot(std::shared_ptr<PluginInterface> Plugin);

        /**
         * @brief
         *   @if LANG_CN 停止所有机器人并等待对应线程结束。
         *   @endif
         *   @if LANG_EN Stops all bots and waits for the corresponding threads to finish.
         *   @endif
         */
        void StopAll();
    private:

        /**
         * @brief
         *   @if LANG_CN 表示单个机器人实例的运行数据。
         *   @endif
         *   @if LANG_EN Represents the runtime data of a single bot instance.
         *   @endif
         */
        struct BotInstance {
            std::shared_ptr<PluginInterface> Plugin;
            std::thread Worker;
            std::atomic<bool> Running{true};
            long long LastUpdateID = 0;
        };

        /**
         * @brief
         *   @if LANG_CN 机器人轮询循环，持续调用 Telegram `getUpdates` 接口。
         *   @endif
         *   @if LANG_EN Bot polling loop that continuously calls the Telegram `getUpdates` API.
         *   @endif
         */
        void BotLoop(const std::string& Token);

        TelegramHTTPClient* HTTPClient_;
        std::map<std::string, BotInstance> Bots_;
        std::mutex BotMutex_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_BOTMANAGE_HPP