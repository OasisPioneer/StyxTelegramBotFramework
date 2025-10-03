#include "TerminalUserInterface/TUILogPage.HPP"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

TUILogPage::TUILogPage() {}

ftxui::Element TUILogPage::Rendering() {
    return ftxui::vbox({
        ftxui::text(boost::locale::translate("Log Manage Demo"))
    });
}

ftxui::Component TUILogPage::GetComponent() {
    return ftxui::Renderer([this] { return this->Rendering(); });
}

std::string TUILogPage::PageName() {
    return boost::locale::translate("Log Manage");
}