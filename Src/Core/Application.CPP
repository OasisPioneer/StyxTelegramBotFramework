#include "Core/Application.HPP"

#include "Core/System/EnvironmentSetup.HPP"
#include "Core/System/LogCollector.HPP"
#include "TerminalUserInterface/TUIManage.HPP"

#include <boost/locale.hpp>

Application::Application() : TUIManage_(std::make_unique<TUIManage>()), RunningStatus(false) {}

bool Application::Initialize() {
    std::vector<std::string> Directory = {"DataBase", "Logs", "Plugins"};
    if (EnvironmentSetup::EnsureDirectoryExist(Directory)) {
        LOG_ERROR(boost::locale::translate("Failed to create necessary directories."));
        return false;
    }
    LOG_INFO(boost::locale::translate("Environment initialized successfully."));
    return true;
}

void Application::Start() {
    if (RunningStatus) {
        LOG_WARN(boost::locale::translate("Application is already running."));
        return;
    }
    RunningStatus = true;

    LOG_INFO("Starting background tasks...");
    BotThread_ = std::thread(&Application::BotTask, this);

    LOG_INFO("Starting Terminal User Interface...");

    // TUIManage TUI;
    // TUI.Show();
    TUIManage_->Show();

    LOG_INFO("UI closed. Shutting down background tasks...");
    RunningStatus = false;

    // 4. 等待后台线程结束
    if (BotThread_.joinable()) {
        BotThread_.join();
    }

    LOG_INFO("Application shut down gracefully.");
}

void Application::BotTask() {
    using namespace std::chrono_literals;
    int counter = 0;
}

Application::~Application() {
    if (BotThread_.joinable()) {
        BotThread_.join();
    }
}