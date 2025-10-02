#include "TerminalUserInterface/TUISettingsPage.HPP"

TUISettingsPage::TUISettingsPage() {}

ftxui::Element TUISettingsPage::Rendering() {
    return ftxui::vbox({
        ftxui::text(boost::locale::translate("System Settings Demo"))
    });
}

std::string TUISettingsPage::PageName() {
    return boost::locale::translate("System Settings");
}