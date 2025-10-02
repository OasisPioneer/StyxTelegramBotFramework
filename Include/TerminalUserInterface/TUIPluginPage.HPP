#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP

#include "TUIBaseClass.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUIPluginPage : public TUIBaseClass {
    public:
        TUIPluginPage();

        ftxui::Element Rendering() override;
        std::string PageName() override;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP