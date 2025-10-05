#ifndef STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP
#define STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP

#include <string>
#include <vector>
#include <mutex>

struct LogEntries {
    std::string TimeStamp;
    std::string Level;
    std::string Message;
};

class LogCollector {
    public:
        static LogCollector& GetInstance();
        void AddLog(const std::string& Level, const std::string& Message);
        std::vector<LogEntries> GetLogs();
    private:
        std::vector<LogEntries> Logs_;
        std::mutex Mutex_;
};

#define LOG_INFO(Message) LogCollector::GetInstance().AddLog("INFO", Message)
#define LOG_WARN(Message) LogCollector::GetInstance().AddLog("WARN", Message)
#define LOG_ERROR(Message) LogCollector::GetInstance().AddLog("ERROR", Message)

#endif //STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP