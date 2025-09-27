#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKRUNTIME_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKRUNTIME_HPP

#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>

#include "ftxui/component/screen_interactive.hpp"

class FrameworkRunTime {
    public:

        explicit FrameworkRunTime(ftxui::ScreenInteractive& Screen);
        ~FrameworkRunTime();

        FrameworkRunTime(const FrameworkRunTime&) = delete;
        FrameworkRunTime& operator=(const FrameworkRunTime&) = delete;

        std::string GetFormattedTime();

        void STOP();
    private:

        struct TimeStructure {
            long long Year;
            long long Month;
            long long Day;
            long long Hour;
            long long Minute;
            long long Second;
        };

        static void TimerThreadFunction(FrameworkRunTime* Time);
        static TimeStructure DecompositionTime(long long TotalSeconds);

    ftxui::ScreenInteractive& _Screen;

    std::chrono::steady_clock::time_point StartupTime;
    std::atomic<bool> ThreadControl;
    std::thread TimerThread;

    std::mutex TimeMutex;
    std::string FormattingTimeString;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKRUNTIME_HPP