#ifndef STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP
#define STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP

#include "TerminalUserInterface/TUIManage.HPP"

#include <atomic>
#include <thread>
#include <memory>

/**
 * @brief
 *   @if LANG_CN 应用程序的核心入口类，负责协调初始化与运行流程。
 *   @endif
 *   @if LANG_EN Core entry class of the application that coordinates initialization and runtime flow.
 *   @endif
 *
 * @details
 *   @if LANG_CN
 *     - 负责准备运行环境、启动插件及终端界面。
 *     - 使用 RAII 管理内部组件，确保资源在生命周期结束时释放。
 *   @endif
 *   @if LANG_EN
 *     - Prepares the runtime environment, starts plugins and the terminal interface.
 *     - Uses RAII to manage internal components, ensuring resources are released at end of lifecycle.
 *   @endif
 */
class Application {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化终端界面管理器并设置运行状态标记。
         *   @endif
         *   @if LANG_EN Constructor that initializes the terminal UI manager and sets the running flag.
         *   @endif
         */
        Application();

        /**
         * @brief
         *   @if LANG_CN 析构函数，默认行为即可释放所持资源。
         *   @endif
         *   @if LANG_EN Destructor with default behavior to release owned resources.
         *   @endif
         */
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        /**
         * @brief
         *   @if LANG_CN 执行运行前的环境准备工作，例如目录检查与创建。
         *   @endif
         *   @if LANG_EN Performs pre-run environment preparation such as directory verification and creation.
         *   @endif
         *
         * @return
         *   @if LANG_CN 初始化成功返回 `true`，失败返回 `false`。
         *   @endif
         *   @if LANG_EN Returns `true` on successful initialization and `false` on failure.
         *   @endif
         */
        bool Initialize();

        /**
         * @brief
         *   @if LANG_CN 启动应用程序主流程，包括插件加载及终端界面循环。
         *   @endif
         *   @if LANG_EN Starts the main workflow including plugin loading and terminal UI loop.
         *   @endif
         */
        void Start();

    private:
        /**
         * @brief
         *   @if LANG_CN 终端界面管理器的独占指针，负责界面构建与事件循环。
         *   @endif
         *   @if LANG_EN Unique pointer to the terminal UI manager that handles UI construction and event loop.
         *   @endif
         */
        std::unique_ptr<TUIManage> TUIManage_;

        /**
         * @brief
         *   @if LANG_CN 表示应用当前运行状态的原子标记，防止重复启动。
         *   @endif
         *   @if LANG_EN Atomic flag indicating whether the application is running to prevent duplicate starts.
         *   @endif
         */
        std::atomic<bool> RunningStatus;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP