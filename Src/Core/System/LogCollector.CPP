#include "Core/System/LogCollector.HPP"

#include <chrono>
#include <iomanip>
#include <sstream>

LogCollector &LogCollector::GetInstance() {
    static LogCollector instance;
    return instance;
}

void LogCollector::AddLog(const std::string &Level, const std::string &Message) {
    auto Now = std::chrono::system_clock::now();
    auto Time = std::chrono::system_clock::to_time_t(Now);
    std::stringstream SS;
    SS << std::put_time(std::localtime(&Time), "%Y-%m-%d %X");
    std::lock_guard<std::mutex> lock(Mutex_);
    Logs_.push_back({SS.str(), Level, Message});
}

std::vector<LogEntries> LogCollector::GetLogs() {
    std::lock_guard<std::mutex> lock(Mutex_);
    return Logs_;
}
