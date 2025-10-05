#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKLOGGER_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKLOGGER_HPP

#include "LoggerInterface.HPP"
#include "Core/System/LogCollector.HPP"

class FrameworkLogger : public LoggerInterface{
    void Info(const char* Message) override { LOG_INFO(Message); }
    void Warn(const char* Message) override { LOG_WARN(Message); }
    void Error(const char* Message) override { LOG_ERROR(Message); }
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKLOGGER_HPP