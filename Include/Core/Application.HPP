#ifndef STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP
#define STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP

#include "TerminalUserInterface/TUIManage.HPP"

#include <atomic>
#include <thread>
#include <memory>

class Application {
    public:

        Application();
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        bool Initialize();
        void Start();

    private:
        std::unique_ptr<TUIManage> TUIManage_;

        std::thread BotThread_;

        std::atomic<bool> RunningStatus;

        void BotTask();
};

#endif //STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP