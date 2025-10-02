#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP

#include <string>

#include <ftxui/dom/elements.hpp>

class TUIBaseClass {
    public:
        virtual ~TUIBaseClass() = default;

        virtual ftxui::Element Rendering() = 0;
        virtual std::string PageName() = 0;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP