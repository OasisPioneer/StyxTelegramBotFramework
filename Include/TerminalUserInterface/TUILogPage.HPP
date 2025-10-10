#ifndef STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP

#include "TUIBaseClass.HPP"
#include "Core/System/LogCollector.HPP"

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>

/**
 * @brief
 *   @if LANG_CN 日志查看页面，按表格形式展示框架日志。
 *   @endif
 *   @if LANG_EN Log viewing page displaying framework logs in a tabular form.
 *   @endif
 */
class TUILogPage : public TUIBaseClass {
    public:
        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化渲染器与事件处理包装。
         *   @endif
         *   @if LANG_EN Constructor initializing the renderer and event handling wrapper.
         *   @endif
         */
        TUILogPage();

        /**
         * @brief
         *   @if LANG_CN 返回渲染组件，用于嵌入主界面容器。
         *   @endif
         *   @if LANG_EN Returns the rendering component for embedding into the main container.
         *   @endif
         */
        ftxui::Component GetComponent() override;

        /**
         * @brief
         *   @if LANG_CN 生成日志表格的渲染元素。
         *   @endif
         *   @if LANG_EN Produces the rendering element of the log table.
         *   @endif
         */
        ftxui::Element Rendering() override;

        /**
         * @brief
         *   @if LANG_CN 返回页面显示名称。
         *   @endif
         *   @if LANG_EN Returns the display name of the page.
         *   @endif
         */
        std::string PageName() override;
    private:
        int LogLocation = 0;
        ftxui::Component MainComponents_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUILOGPAGE_HPP