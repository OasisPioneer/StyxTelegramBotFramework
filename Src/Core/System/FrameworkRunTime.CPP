#include "Core/System/FrameworkRunTime.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/event.hpp>

FrameworkRunTime::FrameworkRunTime(ftxui::ScreenInteractive& Screen) :
    _Screen(Screen),
    StartupTime(std::chrono::steady_clock::now()),
    ThreadControl(true),
    TimerThread(&FrameworkRunTime::TimerThreadFunction, this)
{
    FormattingTimeString = (
        boost::locale::format(boost::locale::translate("Framework has been running stably for: {1,number} year(s), {2,number} month(s), {3,number} day(s), {4,number} hour(s), {5,number} minute(s), {6,number} second(s)"))
        % 0 % 0 % 0 % 0 % 0 % 0
    ).str();
}

FrameworkRunTime::~FrameworkRunTime() {
    STOP();
}

void FrameworkRunTime::STOP() {
    if (ThreadControl.exchange(false)) {
        if (TimerThread.joinable()) {
            TimerThread.join();
        }
    }
}

std::string FrameworkRunTime::GetFormattedTime() {
    std::lock_guard<std::mutex> Lock(TimeMutex);
    return FormattingTimeString;
}

FrameworkRunTime::TimeStructure FrameworkRunTime::DecompositionTime(long long TotalSeconds) {
    TimeStructure Time{};

    if (TotalSeconds < 0) {
        return Time;
    }

    Time.Second = TotalSeconds % 60;
    long long TotalMinutes = TotalSeconds / 60;
    Time.Minute = TotalMinutes % 60;
    long long TotalHours = TotalMinutes / 60;
    Time.Hour = TotalHours % 24;
    long long TotalDays = TotalHours / 24;

    constexpr double AvgDaysInYear = 365.2425;
    constexpr double AvgDaysInMonth = AvgDaysInYear / 12.0;
    Time.Year = static_cast<long long>(TotalDays / AvgDaysInYear);
    long long DaysRemainingAfterYears = TotalDays - static_cast<long long>(Time.Year * AvgDaysInYear);
    Time.Month = static_cast<long long>(DaysRemainingAfterYears / AvgDaysInMonth);
    Time.Day = static_cast<long long>(DaysRemainingAfterYears) % static_cast<long long>(AvgDaysInMonth);

    return Time;
}

void FrameworkRunTime::TimerThreadFunction(FrameworkRunTime* Time) {
    while (Time->ThreadControl) {

        auto now = std::chrono::steady_clock::now();
        auto ElapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - Time->StartupTime).count();
        TimeStructure T = DecompositionTime(ElapsedSeconds);

        std::stringstream ss;
        ss << boost::locale::translate("Framework has been running stably for: ");

        if (T.Year > 0)   ss << T.Year   << boost::locale::translate(" year(s) ");
        if (T.Month > 0)  ss << T.Month  << boost::locale::translate(" month(s) ");
        if (T.Day > 0)    ss << T.Day    << boost::locale::translate(" day(s) ");
        if (T.Hour > 0)   ss << T.Hour   << boost::locale::translate(" hour(s) ");
        if (T.Minute > 0) ss << T.Minute << boost::locale::translate(" minute(s) ");

        ss << T.Second << boost::locale::translate(" second(s)");

        const std::string TimeString = ss.str();

        {
            std::lock_guard<std::mutex> lock(Time->TimeMutex);
            Time->FormattingTimeString = TimeString;
        }

        Time->_Screen.PostEvent(ftxui::Event::Custom);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}