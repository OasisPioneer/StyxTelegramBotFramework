#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP

#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

/**
 * @brief
 *   @if LANG_CN 终端界面页面的抽象基类，定义统一接口。
 *   @endif
 *   @if LANG_EN Abstract base class for terminal UI pages defining the unified interface.
 *   @endif
 */
class TUIBaseClass {
    public:
        virtual ~TUIBaseClass() = default;

        /**
         * @brief
         *   @if LANG_CN 获取页面的组件对象，用于事件处理与渲染。
         *   @endif
         *   @if LANG_EN Retrieves the component object of the page for event handling and rendering.
         *   @endif
         */
        virtual ftxui::Component GetComponent() = 0;

        /**
         * @brief
         *   @if LANG_CN 生成页面的渲染元素树。
         *   @endif
         *   @if LANG_EN Produces the element tree representing the page rendering.
         *   @endif
         */
        virtual ftxui::Element Rendering() = 0;

        /**
         * @brief
         *   @if LANG_CN 返回页面在菜单列表中的名称。
         *   @endif
         *   @if LANG_EN Returns the display name of the page in the menu list.
         *   @endif
         */
        virtual std::string PageName() = 0;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIBASECLASS_HPP