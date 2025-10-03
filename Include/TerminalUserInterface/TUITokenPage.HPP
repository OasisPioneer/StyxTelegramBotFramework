#ifndef STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP

#include "TUIBaseClass.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

#include <string>

class TUITokenPage : public TUIBaseClass {
    public:
        TUITokenPage();

        ftxui::Component GetComponent() override;
        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        std::string TokenString_;
        ftxui::Component TokenInput_;
        std::string DescriptionString_;
        ftxui::Component DescriptionInput_;

        ftxui::Component AddButton_;

        ftxui::Component MainContainer_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP