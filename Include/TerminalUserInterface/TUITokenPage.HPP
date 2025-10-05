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
        ftxui::Component MainContainer_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUITOKENPAGE_HPP