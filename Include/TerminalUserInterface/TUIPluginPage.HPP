#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP

#include "TUIBaseClass.HPP"
#include "Plugins/PluginManage.HPP"

#include <memory>

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUIPluginPage : public TUIBaseClass {
    public:
        TUIPluginPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        std::unique_ptr<PluginManage> PluginManage_;
        ftxui::Component MainComponents_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIPLUGINPAGE_HPP