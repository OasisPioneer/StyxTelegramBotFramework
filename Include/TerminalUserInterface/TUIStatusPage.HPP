#ifndef STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP

#include "TUIBaseClass.HPP"

#include <atomic>
#include <chrono>
#include <string>
#include <thread>

#include <boost/locale.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

/**
 * @brief
 *   @if LANG_CN 状态展示页面，动态呈现运行时间、插件数量等信息。
 *   @endif
 *   @if LANG_EN Status display page showing runtime duration, plugin count, and more.
 *   @endif
 */
class TUIStatusPage : public TUIBaseClass {
    public:
        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化页面渲染器并创建刷新线程。
         *   @endif
         *   @if LANG_EN Constructor initializing the page renderer and spawning the refresh thread.
         *   @endif
         */
        TUIStatusPage(ftxui::ScreenInteractive& Screen);

        /**
         * @brief
         *   @if LANG_CN 析构函数，终止刷新线程并等待其结束。
         *   @endif
         *   @if LANG_EN Destructor that stops the refresh thread and waits for completion.
         *   @endif
         */
        ~TUIStatusPage();

        /**
         * @brief
         *   @if LANG_CN 返回页面的主组件以嵌入到容器中。
         *   @endif
         *   @if LANG_EN Returns the main component of the page for container embedding.
         *   @endif
         */
        ftxui::Component GetComponent() override;

        /**
         * @brief
         *   @if LANG_CN 渲染当前状态视图，包括运行时长与插件统计。
         *   @endif
         *   @if LANG_EN Renders the current status view including runtime duration and plugin statistics.
         *   @endif
         */
        ftxui::Element Rendering() override;

        /**
         * @brief
         *   @if LANG_CN 返回页面在菜单中的显示名称。
         *   @endif
         *   @if LANG_EN Returns the display name of the page in the menu.
         *   @endif
         */
        std::string PageName() override;
    private:
        /**
         * @brief
         *   @if LANG_CN 周期性发布事件以更新界面的后台线程。
         *   @endif
         *   @if LANG_EN Background thread periodically posting events to refresh the UI.
         *   @endif
         */
        void AnimationThread();

        std::chrono::steady_clock::time_point StartupTime_;

        ftxui::Component MainComponents_;

        ftxui::ScreenInteractive& Screen_;
        std::thread TimerThread_;
        std::atomic<bool> StopThread_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_TUISTATUSPAGE_HPP