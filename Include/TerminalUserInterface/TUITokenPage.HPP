#ifndef STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP

#include "TUIBaseClass.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

class TUITokenPage : public TUIBaseClass {
    public:
        TUITokenPage();

        ftxui::Element Rendering() override;
        std::string PageName() override;
    private:
        std::string TokenString_;
        ftxui::Component TokenInput_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP