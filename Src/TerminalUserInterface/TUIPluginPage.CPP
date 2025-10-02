#include "TerminalUserInterface/TUIPluginPage.HPP"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

TUIPluginPage::TUIPluginPage() {}

ftxui::Element TUIPluginPage::Rendering() {
    return ftxui::vbox({
        ftxui::text(boost::locale::translate("Running Status Demo"))
    });
}

std::string TUIPluginPage::PageName() {
    return boost::locale::translate("Plugins Manage");
}