#include "TerminalUserInterface/TUIManage.HPP"

#include <boost/locale.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

#include "TerminalUserInterface/TUIStatusPage.HPP"
#include "TerminalUserInterface/TUIPluginPage.HPP"
#include "TerminalUserInterface/TUILogPage.HPP"
#include "TerminalUserInterface/TUISettingsPage.HPP"

constexpr int LeftPanelWidth = 25;

TUIManage::TUIManage() : Screen_(ftxui::ScreenInteractive::Fullscreen()) {
    TUIPage_.push_back(std::make_unique<TUIStatusPage>(this->Screen_));
    TUIPage_.push_back(std::make_unique<TUIPluginPage>());
    TUIPage_.push_back(std::make_unique<TUILogPage>());
    TUIPage_.push_back(std::make_unique<TUISettingsPage>());
    for (const auto& Page : TUIPage_) {
        MenuArray_.push_back(Page->PageName());
    }
}

void TUIManage::Show() {

    std::vector<ftxui::Component> AllPageMainComponents;
    for (const auto& Page : TUIPage_) {
        AllPageMainComponents.push_back(Page->GetComponent());
    }

    auto TabContainer = ftxui::Container::Tab(AllPageMainComponents, &SelectedTab_);

    std::vector<ftxui::Component> MenuButton;
    for (int i =0; i < MenuArray_.size(); ++i) {
        MenuButton.push_back(ftxui::Button(
            &MenuArray_[i],
            [this, i] {this->SelectedTab_ = i;},
            ftxui::ButtonOption::Ascii()
            )| ftxui::center | ftxui::border);
    }
    auto MenuContainer = ftxui::Container::Vertical(MenuButton);

    MainContainer_ = ftxui::Container::Horizontal({
        MenuContainer,
        TabContainer,
    });

    auto Renderer = ftxui::Renderer(MainContainer_, [this] {return this->BuildTUI();});

    auto EventCapture = ftxui::CatchEvent(Renderer, [&](const ftxui::Event &event) {
        if (event == ftxui::Event::Character('q')) {
            // Screen_.Exit();
            this->Exit();
            return true;
        }
        return false;
    });

    Screen_.Loop(EventCapture);
}

void TUIManage::RefreshEvent() {
    Screen_.PostEvent(ftxui::Event::Custom);
}

void TUIManage::Exit() {
    Screen_.Exit();
}

ftxui::Element TUIManage::BuildTUI() const {

    auto LeftPane = MainContainer_->ChildAt(0)->Render() | ftxui::vscroll_indicator | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, LeftPanelWidth) ;
    auto RightPane = MainContainer_->ChildAt(1)->Render() | ftxui::flex;

    auto MainArea = ftxui::hbox({
        LeftPane,
        ftxui::separator(),
        RightPane
    }) | ftxui::flex;

    return ftxui::vbox({
        BuildHeaderArea(),
        ftxui::separator(),
        MainArea
    }) | ftxui::border;
}

ftxui::Element TUIManage::BuildHeaderArea() {
    auto HeaderLayout = ftxui::hbox({
        ftxui::text(boost::locale::translate("Styx Studio")) | ftxui::bold | ftxui::center | ftxui::size(ftxui::WIDTH, ftxui::EQUAL,LeftPanelWidth),
        ftxui::separator(),
        ftxui::filler(),
        ftxui::hbox({
            ftxui::text(boost::locale::translate("Demo Announcement")) | ftxui::bold | ftxui::center,
        }),
        ftxui::filler()
    });
    return HeaderLayout;
}

ftxui::Element TUIManage::BuildContentArea() const {
    if (SelectedTab_ < 0 || SelectedTab_ >= TUIPage_.size()) {
        return ftxui::text(boost::locale::translate("Error: Page index out of range.")) | ftxui::center;
    }
    auto& SelectedPage = TUIPage_[SelectedTab_];
    // return ftxui::text(SelectedPage->PageName()) | ftxui::bold, SelectedPage->Rendering() | ftxui::flex;
    return SelectedPage->GetComponent()->Render() | ftxui::flex;
}