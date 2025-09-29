#include "Core/Application.HPP"
#include "Core/System/EnvironmentSetup.HPP"

Application::Application() : RunningStatus(false) {

}

bool Application::Initialize() {
    std::vector<std::string> Directory = {"DataBase", "Logs", "Plugins"};
    if (EnvironmentSetup::EnsureDirectoryExist(Directory)) {
        return false;
    }
    return true;
}

Application::~Application() {

}