#include "Core/Application.HPP"
#include "Core/System/EnvironmentSetup.HPP"
#include "TerminalUserInterface/TUIManage.HPP"

Application::Application() : RunningStatus(false) {}

bool Application::Initialize() {
    std::vector<std::string> Directory = {"DataBase", "Logs", "Plugins"};
    if (EnvironmentSetup::EnsureDirectoryExist(Directory)) {
        return false;
    }
    return true;
}

void Application::Start() {
    if (RunningStatus) {
        return;
    }
    RunningStatus = true;

    TUIManage TUI;
    TUI.Show();
}

Application::~Application() {

}