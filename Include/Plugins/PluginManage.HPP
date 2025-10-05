#ifndef STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP

#include "PluginInterface.HPP"

#include <string>
#include <vector>
#include <memory>

class PluginInterface;
class FrameworkServiceInterface;

struct PluginInfo {
    std::shared_ptr<PluginInterface> Instance;
    void* Handle;
    std::string Path;
    std::unique_ptr<FrameworkServiceInterface> Service;
};

class PluginManage {
    public:

        PluginManage();
        ~PluginManage();

        void LoadingPlugins(const std::string& DirectoryPath);
        const std::vector<PluginInfo>& GetLoadedPlugins() const;
    private:
        std::vector<PluginInfo> LoadedPlugins_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_PLUGINMANAGE_HPP