#ifndef STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP

#include "PluginInterface.HPP"

#include <string>
#include <vector>
#include <memory>

class PluginInterface;
class FrameworkServiceInterface;

/**
 * @brief
 *   @if LANG_CN 描述单个插件实例及其运行时资源的结构体。
 *   @endif
 *   @if LANG_EN Structure describing a single plugin instance and its runtime resources.
 *   @endif
 *
 * @details
 *   @if LANG_CN
 *     - `Instance` 保存插件接口指针，使用自定义删除器释放。
 *     - `Handle` 对应动态库句柄，用于在需要时关闭。
 *     - `Service` 提供框架服务访问，例如日志。
 *   @endif
 *   @if LANG_EN
 *     - `Instance` holds the plugin interface pointer with a custom deleter.
 *     - `Handle` stores the dynamic library handle for potential closing.
 *     - `Service` offers access to framework services such as logging.
 *   @endif
 */
struct PluginInfo {
    std::shared_ptr<PluginInterface> Instance;
    void* Handle;
    std::string Path;
    std::unique_ptr<FrameworkServiceInterface> Service;
};

/**
 * @brief
 *   @if LANG_CN 插件管理器，负责扫描、加载并维护插件生命周期。
 *   @endif
 *   @if LANG_EN Plugin manager responsible for scanning, loading, and maintaining plugin lifecycles.
 *   @endif
 */
class PluginManage {
    public:

        /**
         * @brief
         *   @if LANG_CN 构造函数，在创建时记录管理器初始化流程。
         *   @endif
         *   @if LANG_EN Constructor that logs the initialization of the manager.
         *   @endif
         */
        PluginManage();

        /**
         * @brief
         *   @if LANG_CN 析构函数，在销毁时卸载已加载插件。
         *   @endif
         *   @if LANG_EN Destructor that unloads loaded plugins upon destruction.
         *   @endif
         */
        ~PluginManage();

        /**
         * @brief
         *   @if LANG_CN 扫描指定目录中的动态库并尝试加载符合接口的插件。
         *   @endif
         *   @if LANG_EN Scans the specified directory and attempts to load dynamic libraries implementing the plugin interface.
         *   @endif
         *
         * @param DirectoryPath
         *   @if LANG_CN 插件所在目录的路径。
         *   @endif
         *   @if LANG_EN Path to the directory containing plugins.
         *   @endif
         */
        void LoadingPlugins(const std::string& DirectoryPath);

        /**
         * @brief
         *   @if LANG_CN 获取当前已加载插件的信息集合。
         *   @endif
         *   @if LANG_EN Retrieves the collection of currently loaded plugin information.
         *   @endif
         *
         * @return
         *   @if LANG_CN 返回内部存储的 `PluginInfo` 向量的常量引用。
         *   @endif
         *   @if LANG_EN Returns a constant reference to the internally stored vector of `PluginInfo`.
         *   @endif
         */
        const std::vector<PluginInfo>& GetLoadedPlugins() const;
    private:
        std::vector<PluginInfo> LoadedPlugins_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP