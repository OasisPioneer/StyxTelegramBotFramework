#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP

#include "FrameworkServiceInterface.HPP"
#include "FrameworkLogger.HPP"

#include <memory>

/**
 * @brief
 *   @if LANG_CN 框架服务入口，为插件提供日志等通用能力。
 *   @endif
 *   @if LANG_EN Entry point for framework services offering common capabilities such as logging to plugins.
 *   @endif
 */
class FrameworkServices : public FrameworkServiceInterface {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，初始化框架日志器实例。
         *   @endif
         *   @if LANG_EN Constructor that initializes the framework logger instance.
         *   @endif
         */
        FrameworkServices() : Logger_(std::make_unique<FrameworkLogger>()){}

        /**
         * @brief
         *   @if LANG_CN 返回日志接口指针供插件使用。
         *   @endif
         *   @if LANG_EN Returns the logger interface pointer for plugin usage.
         *   @endif
         *
         * @return
         *   @if LANG_CN `LoggerInterface` 指针，用于记录框架级日志。
         *   @endif
         *   @if LANG_EN Pointer to `LoggerInterface` enabling framework-level logging.
         *   @endif
         */
        LoggerInterface* GetLogger() override {
            return Logger_.get();
        }
    private:
        std::unique_ptr<FrameworkLogger> Logger_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP