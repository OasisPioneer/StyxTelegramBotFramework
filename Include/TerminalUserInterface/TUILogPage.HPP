#ifndef STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP

#include "TUIBaseClass.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUILogPage : public TUIBaseClass {
    public:
        TUILogPage();

        ftxui::Element Rendering() override;
        std::string PageName() override;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP