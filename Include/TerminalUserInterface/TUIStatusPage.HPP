#ifndef STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP

#include "TUIBaseClass.HPP"

#include <atomic>
#include <chrono>
#include <string>
#include <thread>

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

class TUIStatusPage : public TUIBaseClass {
    public:
        TUIStatusPage(ftxui::ScreenInteractive& Screen);
        ~TUIStatusPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        void AnimationThread();

        std::chrono::steady_clock::time_point StartupTime_;

        ftxui::Component MainComponents_;

        ftxui::ScreenInteractive& Screen_;
        std::thread TimerThread_;
        std::atomic<bool> StopThread_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP