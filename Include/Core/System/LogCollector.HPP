#ifndef STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP
#define STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP

#include <string>
#include <vector>
#include <mutex>

/**
 * @brief
 *   @if LANG_CN 表示单条日志记录的基础数据结构。
 *   @endif
 *   @if LANG_EN Represents the fundamental data structure of a single log record.
 *   @endif
 */
struct LogEntries {
    std::string TimeStamp;
    std::string Level;
    std::string Message;
};

/**
 * @brief
 *   @if LANG_CN 单例日志采集器，负责集中存储并提供线程安全的日志访问接口。
 *   @endif
 *   @if LANG_EN Singleton log collector providing centralized and thread-safe access to log entries.
 *   @endif
 *
 * @details
 *   @if LANG_CN
 *     - 使用互斥锁保护内部缓存，确保多线程环境下写入安全。
 *     - 通过静态获取接口提供全局访问点。
 *   @endif
 *   @if LANG_EN
 *     - Uses a mutex to guard the internal buffer ensuring safe writes in multi-threaded environments.
 *     - Exposes a global access point via a static getter.
 *   @endif
 */
class LogCollector {
    public:

        /**
         * @brief
         *   @if LANG_CN 获取日志收集器的全局唯一实例。
         *   @endif
         *   @if LANG_EN Retrieves the globally unique instance of the log collector.
         *   @endif
         *
         * @return
         *   @if LANG_CN 返回单例对象的引用。
         *   @endif
         *   @if LANG_EN Returns a reference to the singleton instance.
         *   @endif
         */
        static LogCollector& GetInstance();

        /**
         * @brief
         *   @if LANG_CN 新增一条日志记录并附加时间戳。
         *   @endif
         *   @if LANG_EN Appends a new log entry along with a timestamp.
         *   @endif
         *
         * @param Level
         *   @if LANG_CN 日志等级，例如 INFO、WARN、ERROR。
         *   @endif
         *   @if LANG_EN Log level such as INFO, WARN, or ERROR.
         *   @endif
         * @param Message
         *   @if LANG_CN 日志内容字符串。
         *   @endif
         *   @if LANG_EN Log message content.
         *   @endif
         */
        void AddLog(const std::string& Level, const std::string& Message);

        /**
         * @brief
         *   @if LANG_CN 返回当前缓存的全部日志副本。
         *   @endif
         *   @if LANG_EN Returns a copy of all currently buffered logs.
         *   @endif
         *
         * @return
         *   @if LANG_CN 日志列表的副本，调用方可自由处理。
         *   @endif
         *   @if LANG_EN A copy of the log list for the caller to consume freely.
         *   @endif
         */
        std::vector<LogEntries> GetLogs();
    private:
        std::vector<LogEntries> Logs_;
        std::mutex Mutex_;
};

#define LOG_INFO(Message) LogCollector::GetInstance().AddLog("INFO", Message)
#define LOG_WARN(Message) LogCollector::GetInstance().AddLog("WARN", Message)
#define LOG_ERROR(Message) LogCollector::GetInstance().AddLog("ERROR", Message)

#endif //STYXTELEGRAMBOTFRAMEWORK_LOGCOLLECTOR_HPP