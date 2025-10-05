#ifndef STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP

#include "TUIBaseClass.HPP"

#include <chrono>
#include <string>

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUIStatusPage : public TUIBaseClass {
    public:
        TUIStatusPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        std::chrono::steady_clock::time_point StartupTime_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP