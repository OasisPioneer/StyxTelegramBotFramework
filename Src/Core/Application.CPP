#include "Core/Application.HPP"

#include "Core/System/EnvironmentSetup.HPP"
#include "Core/System/LogCollector.HPP"
#include "TerminalUserInterface/TUIManage.HPP"

#include "NetWork/TelegramHTTPClient.HPP"
#include "Plugins/PluginManage.HPP"
#include "Plugins/BotManage.HPP"

#include <boost/locale.hpp>

Application::Application() : TUIManage_(std::make_unique<TUIManage>()), RunningStatus(false) {}

bool Application::Initialize() {
    std::vector<std::string> Directory = {"DataBase", "Logs", "Plugins"};
    if (!EnvironmentSetup::EnsureDirectoryExist(Directory)) {
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

    TelegramHTTPClient HTTPClient;
    BotManage BotManager(&HTTPClient);

    PluginManage Plugin;
    Plugin.LoadingPlugins("Plugins");

    for (const auto& plugin_info : Plugin.GetLoadedPlugins()) {
        BotManager.RegisterBot(plugin_info.Instance);
    }

    LOG_INFO("Starting Terminal User Interface...");

    // TUIManage TUI;
    // TUI.Show();
    TUIManage_->Show();

    LOG_INFO("UI closed. Shutting down background tasks...");
    RunningStatus = false;

    LOG_INFO("Application shut down gracefully.");
}

Application::~Application() {}