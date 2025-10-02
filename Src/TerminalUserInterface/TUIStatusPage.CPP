#include "TerminalUserInterface/TUIStatusPage.HPP"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

TUIStatusPage::TUIStatusPage() {}

ftxui::Element TUIStatusPage::Rendering() {
    return ftxui::vbox({
        ftxui::text(boost::locale::translate("Running Status Demo"))
    });
}

std::string TUIStatusPage::PageName() {
    return boost::locale::translate("Running Status");
}