#include "TerminalUserInterface/TUITokenPage.HPP"

#include <ftxui/dom/elements.hpp>

TUITokenPage::TUITokenPage() {
    TokenInput_ = ftxui::Input(&TokenString_, boost::locale::translate("Bot Token").str()) | ftxui::vcenter;
    DescriptionInput_ = ftxui::Input(&DescriptionString_, boost::locale::translate("Description").str()) | ftxui::vcenter;

    AddButton_ = ftxui::Button(boost::locale::translate("Add Bot Token").str(), [this] {
        TokenString_.clear();
        DescriptionString_.clear();
    });

    MainContainer_ = ftxui::Container::Horizontal({
        TokenInput_,
        DescriptionInput_,
        AddButton_,
    });
}

ftxui::Element TUITokenPage::Rendering() {

    auto TokenForm = ftxui::hbox({
        ftxui::text(boost::locale::translate("Bot Token: ").str()) | ftxui::vcenter,
        TokenInput_->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
        ftxui::text(boost::locale::translate("Description: ").str()) | ftxui::vcenter,
        DescriptionInput_->Render() | ftxui::flex,
        AddButton_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3)
    }) | ftxui::border;

    auto FinalLayout = ftxui::vbox({
        TokenForm
    });

    return FinalLayout;
}

std::string TUITokenPage::PageName() {
    return boost::locale::translate("Token Manage");
}

ftxui::Component TUITokenPage::GetComponent() {
    return ftxui::Renderer(MainContainer_, [this] {
        return this->Rendering();
    });
}