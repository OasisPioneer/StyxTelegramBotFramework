#include "TerminalUserInterface/TUISettingsPage.HPP"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

TUISettingsPage::TUISettingsPage() {}

ftxui::Element TUISettingsPage::Rendering() {
    return ftxui::vbox({
        ftxui::text(boost::locale::translate("System Settings Demo"))
    });
}

std::string TUISettingsPage::PageName() {
    return boost::locale::translate("System Settings");
}

ftxui::Component TUISettingsPage::GetComponent() {
    return ftxui::Renderer([this] { return this->Rendering(); });
}