#ifndef STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP

#include <string>
#include <vector>
#include <memory>

#include "TerminalUserInterface/TUIBaseClass.HPP"

#include <ftxui/component/screen_interactive.hpp>

/**
 * @brief
 *   @if LANG_CN 终端界面管理器，负责构建并运行多页面 TUI。
 *   @endif
 *   @if LANG_EN Terminal UI manager responsible for constructing and running the multi-page TUI.
 *   @endif
 */
class TUIManage {
    public:
        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化页面集合与主界面所需组件。
         *   @endif
         *   @if LANG_EN Constructor initializing the page collection and components required by the main UI.
         *   @endif
         */
        TUIManage();

        /**
         * @brief
         *   @if LANG_CN 向界面发布自定义事件以触发重绘。
         *   @endif
         *   @if LANG_EN Posts a custom event to the interface to trigger redraw.
         *   @endif
         */
        void RefreshEvent();

        /**
         * @brief
         *   @if LANG_CN 请求终端界面退出。
         *   @endif
         *   @if LANG_EN Requests the terminal interface to exit.
         *   @endif
         */
        void Exit();

        /**
         * @brief
         *   @if LANG_CN 显示终端界面并进入事件循环。
         *   @endif
         *   @if LANG_EN Displays the terminal interface and enters the event loop.
         *   @endif
         */
        void Show();
    private:
        /**
         * @brief
         *   @if LANG_CN 构建完整界面布局的渲染树。
         *   @endif
         *   @if LANG_EN Builds the rendering tree of the complete interface layout.
         *   @endif
         */
        ftxui::Element BuildTUI() const;

        /**
         * @brief
         *   @if LANG_CN 构建顶部标题区域。
         *   @endif
         *   @if LANG_EN Builds the top header section.
         *   @endif
         */
        static ftxui::Element BuildHeaderArea();

        /**
         * @brief
         *   @if LANG_CN 根据当前选中的标签页生成内容区域。
         *   @endif
         *   @if LANG_EN Generates the content area according to the currently selected tab.
         *   @endif
         */
        ftxui::Element BuildContentArea() const;

        ftxui::ScreenInteractive Screen_;
        ftxui::Component MainContainer_;

        /**
         * @brief
         *   @if LANG_CN 存储页面名称的菜单数组，用于生成左侧导航。
         *   @endif
         *   @if LANG_EN Menu array storing page names for generating the left navigation.
         *   @endif
         */
        std::vector<std::string> MenuArray_;
        int SelectedTab_ = 0;
        /**
         * @brief
         *   @if LANG_CN 保存各页面实例的容器，确保生命周期与界面一致。
         *   @endif
         *   @if LANG_EN Holds the page instances ensuring their lifecycle matches the UI.
         *   @endif
         */
        std::vector<std::unique_ptr<TUIBaseClass>> TUIPage_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUIMANAGE_HPP