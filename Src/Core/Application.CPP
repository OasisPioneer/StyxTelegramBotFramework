#include "Core/Application.HPP"

#include <chrono>
#include <thread>

#include <boost/locale.hpp>

#include "Core/System/SystemStructure.HPP"

bool Application::Initialize() {
    const SystemStructure SS;
    RequiredDirectories = SS.DirectoryArray;
    for (const auto& Directory : RequiredDirectories) {
        if (!SS.CheckCreateDirectory(Directory)) {
            return false;
        }
    }
    return true;
}

int Application::Run() {
    if (Running_Status) {
        return -1;
    }
    Running_Status = true;
    while (Running_Status) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

void Application::Stop() {
    Running_Status.exchange(false);
}
