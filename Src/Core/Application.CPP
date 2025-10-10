#include "Core/Application.HPP"

#include "Core/System/EnvironmentSetup.HPP"
#include "Core/System/LogCollector.HPP"
#include "TerminalUserInterface/TUIManage.HPP"

#include "NetWork/TelegramHTTPClient.HPP"
#include "Plugins/PluginManage.HPP"
#include "Plugins/BotManage.HPP"

#include <boost/locale.hpp>

/**
 * @brief
 *   @if LANG_CN 构造函数，创建终端界面管理器并初始化运行状态标记。
 *   @endif
 *   @if LANG_EN Constructor that creates the terminal UI manager and initializes the running state flag.
 *   @endif
 */
Application::Application() : TUIManage_(std::make_unique<TUIManage>()), RunningStatus(false) {}

/**
 * @brief
 *   @if LANG_CN 检查并创建运行所需的基础目录。
 *   @endif
 *   @if LANG_EN Checks and creates fundamental directories required for runtime.
 *   @endif
 *
 * @return
 *   @if LANG_CN 成功返回 `true`，若目录无法创建则返回 `false`。
 *   @endif
 *   @if LANG_EN Returns `true` on success, or `false` if directories cannot be created.
 *   @endif
 */
bool Application::Initialize() {
    std::vector<std::string> Directory = {"DataBase", "Logs", "Plugins"};
    if (!EnvironmentSetup::EnsureDirectoryExist(Directory)) {
        LOG_ERROR(boost::locale::translate("Failed to create necessary directories."));
        return false;
    }
    LOG_INFO(boost::locale::translate("Environment initialized successfully."));
    return true;
}

/**
 * @brief
 *   @if LANG_CN 启动应用程序主循环，负责加载插件并展示终端界面。
 *   @endif
 *   @if LANG_EN Starts the application's main loop, loading plugins and presenting the terminal interface.
 *   @endif
 */
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