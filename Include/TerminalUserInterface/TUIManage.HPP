#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

struct ApplicationStatus {
    int SelectTag = 0;

};

class TUIManage {
    public:
        TUIManage() = default;
        ~TUIManage() = default;

        TUIManage(const TUIManage&) = delete;
        TUIManage& operator=(const TUIManage&) = delete;
        TUIManage(const TUIManage&&) = delete;
        TUIManage& operator=(const TUIManage&&) = delete;


};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP