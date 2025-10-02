#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP

#include <string>
#include <vector>
#include <memory>

#include "TerminalUserInterface/TUIBaseClass.HPP"

#include <ftxui/component/screen_interactive.hpp>

class TUIManage {
    public:
        TUIManage();
        void Show();
    private:
        ftxui::Element BuildTUI() const;

        static ftxui::Element BuildHeaderArea();
        ftxui::Element BuildContentArea() const;

        ftxui::ScreenInteractive Screen_;
        ftxui::Component MainContainer_;

        std::vector<std::string> MenuArray_;
        int SelectedTab_ = 0;
        std::vector<std::unique_ptr<TUIBaseClass>> TUIPage_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP