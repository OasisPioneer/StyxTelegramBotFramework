#ifndef STYXTELEGRAMBOTFRAMEWORK_TUISETTINGSPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUISETTINGSPAGE_HPP

#include "TUIBaseClass.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUISettingsPage : public TUIBaseClass {
    public:
        TUISettingsPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUISETTINGSPAGE_HPP