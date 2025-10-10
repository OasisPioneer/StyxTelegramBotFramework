#include "TerminalUserInterface/TUIStatusPage.HPP"
#include "Core/System/EnvironmentSetup.HPP"

#include <iomanip>

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include "Core/Application.HPP"

TUIStatusPage::TUIStatusPage(ftxui::ScreenInteractive& Screen) : StartupTime_(std::chrono::steady_clock::now()), Screen_(Screen), StopThread_(false) {
    MainComponents_ = ftxui::Renderer([this] { return this->Rendering(); });
    TimerThread_ = std::thread(&TUIStatusPage::AnimationThread, this);
}

ftxui::Element TUIStatusPage::Rendering() {

    auto Now = std::chrono::steady_clock::now();
    auto Duration = std::chrono::duration_cast<std::chrono::seconds>(Now - StartupTime_);
    long long TotalSeconds = Duration.count();

    long long Hour = TotalSeconds / 3600;
    long long Minute = (TotalSeconds % 3600) / 60;
    long long Second = TotalSeconds % 60;

    std::stringstream TimeFlow;
    TimeFlow << std::setw(2) << std::setfill('0') << Hour << ":"
                << std::setw(2) << std::setfill('0') << Minute << ":"
                << std::setw(2) << std::setfill('0') << Second;
    std::string RuntimeString = TimeFlow.str();

    const int WindowHeight = 5;

    auto TokenCount = ftxui::window(
        ftxui::text(boost::locale::translate("Token Count")),
        ftxui::text("0") | ftxui::center
    ) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, WindowHeight) | ftxui::flex_grow;

    EnvironmentSetup Environment;
    std::string Count = std::to_string(Environment.GetDirectoryPluginCount("Plugins"));
    auto PluginCount = ftxui::window(
        ftxui::text(boost::locale::translate("Plugin Count")),
        ftxui::text(Count) | ftxui::center
    ) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, WindowHeight) | ftxui::flex_grow;

    auto RunTime = ftxui::window(
        ftxui::text(boost::locale::translate("Run Time")),
        ftxui::text(RuntimeString) | ftxui::center
    ) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, WindowHeight) | ftxui::flex_grow;

    auto RunningStatus = ftxui::hbox({
        ftxui::filler(),
        TokenCount,
        ftxui::filler(),
        PluginCount,
        ftxui::filler(),
        RunTime,
        ftxui::filler(),
    });

    auto FinalLayout = ftxui::vbox({
        ftxui::filler(),
        RunningStatus,
        ftxui::filler(),
        ftxui::filler()
    });

    return FinalLayout;
}

std::string TUIStatusPage::PageName() {
    return boost::locale::translate("Running Status");
}

ftxui::Component TUIStatusPage::GetComponent() {
    // return ftxui::Renderer([this] { return this->Rendering(); });
    return MainComponents_;
}

void TUIStatusPage::AnimationThread() {
    using namespace std::chrono_literals;
    while (!StopThread_) {
        Screen_.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(500ms);
    }
}

TUIStatusPage::~TUIStatusPage() {
    StopThread_ = true;
    if (TimerThread_.joinable()) {
        TimerThread_.join();
    }
}