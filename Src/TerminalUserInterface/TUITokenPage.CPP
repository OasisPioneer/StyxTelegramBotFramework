#include "TerminalUserInterface/TUITokenPage.HPP"

#include <ftxui/dom/elements.hpp>

TUITokenPage::TUITokenPage() {
    TokenString_ = boost::locale::translate("Your Telegram Bot Token");
    TokenInput_ = ftxui::Input(&TokenString_, boost::locale::translate("Token").str());
}

ftxui::Element TUITokenPage::Rendering() {
    return ftxui::vbox({
            ftxui::text(boost::locale::translate("Token Manage Demo"))
    });
}

std::string TUITokenPage::PageName() {
    return boost::locale::translate("Token Manage");
}