#ifndef STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP

#include "TUIBaseClass.HPP"
#include "Core/System/LogCollector.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUILogPage : public TUIBaseClass {
    public:
        TUILogPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        int LogLocation = 0;
        ftxui::Component MainComponents_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP