#ifndef STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP
#define STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP

#include <string>
#include <memory>

class SingletonInstanceControlIMPL;

/**
 * @brief
 *   @if LANG_CN 用于确保应用程序单例运行的RAII控制器。
 *   @endif
 *   @if LANG_EN An RAII controller to ensure a single instance of the application.
 *   @endif
 *
 * @details
 *   @if LANG_CN
 *     此类通过在构造时获取系统级锁并在析构时释放它，来防止应用程序的多个实例同时运行。
 *     如果锁已被另一实例持有，构造函数将抛出异常。
 *     它被设计为不可拷贝和不可移动。
 *   @endif
 *   @if LANG_EN
 *     This class prevents multiple instances of an application from running concurrently by acquiring a
 *     system-wide lock on construction and releasing it on destruction. The constructor will throw an
 *     exception if the lock is already held by another instance. It is designed to be non-copyable
 *     and non-movable.
 *   @endif
 */
class SingletonInstanceControl {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，尝试获取实例锁。
         *   @endif
         *   @if LANG_EN Constructor that attempts to acquire the instance lock.
         *   @endif
         *
         * @param InstanceID
         *   @if LANG_CN 用于创建系统级锁的唯一标识符。
         *   @endif
         *   @if LANG_EN A unique identifier used to create the system-wide lock.
         *   @endif
         * @throw std::runtime_error
         *   @if LANG_CN 如果实例已在运行，则抛出。
         *   @endif
         *   @if LANG_EN Thrown if an instance is already running.
         *   @endif
         */
        explicit SingletonInstanceControl(const std::string& InstanceID);

        /**
         * @brief
         *   @if LANG_CN 析构函数，自动释放实例锁。
         *   @endif
         *   @if LANG_EN Destructor that automatically releases the instance lock.
         *   @endif
         */
        ~SingletonInstanceControl();

        SingletonInstanceControl(SingletonInstanceControl const&) = delete;
        SingletonInstanceControl& operator=(SingletonInstanceControl const&) = delete;
        SingletonInstanceControl(SingletonInstanceControl&&) = delete;
        SingletonInstanceControl& operator=(SingletonInstanceControl&&) = delete;

    private:

        /**
         * @brief
         *   @if LANG_CN 指向具体实现的指针（PIMPL）。
         *   @endif
         *   @if LANG_EN Pointer to the implementation (PIMPL).
         *   @endif
         */
        std::unique_ptr<SingletonInstanceControlIMPL> PIMPL;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP