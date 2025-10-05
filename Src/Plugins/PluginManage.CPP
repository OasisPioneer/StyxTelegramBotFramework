#include "Plugins/PluginManage.HPP"
#include "Core/System/LogCollector.HPP"
#include "Core/System/FrameworkServices.HPP"
#include "PluginInterface.HPP"

#include <dlfcn.h>

#include <boost/locale.hpp>
#include <boost/filesystem.hpp>

PluginManage::PluginManage() {
    LOG_INFO(boost::locale::translate("PluginManager initialized."));
}

void PluginManage::LoadingPlugins(const std::string& DirectoryPath) {
    LOG_INFO(boost::locale::translate("Scan the following plugins: ").str() + DirectoryPath);
    if (!boost::filesystem::exists(DirectoryPath) || !boost::filesystem::is_directory(DirectoryPath)) {
        LOG_ERROR(boost::locale::translate("Plugin directory does not exist or is not a directory: ").str() + DirectoryPath);
        return;
    }


    for (const auto& Entry : boost::filesystem::directory_iterator(DirectoryPath)) {
        if (Entry.is_regular_file() && Entry.path().extension() == ".so" || Entry.path().extension() == ".dylib" || Entry.path().extension() == ".dll") {
            const std::string Path = Entry.path().string();
            LOG_INFO(boost::locale::translate("Attempting to load plugin: ").str() + Path);

            void* Handle = dlopen(Path.c_str(), RTLD_LAZY);
            if (!Handle) {
                LOG_ERROR("Failed to load plugin " + Path + ". Error: " + dlerror());
                continue;
            }

            CreatePluginFunction CreateFunction = (CreatePluginFunction)dlsym(Handle, "CreatePlugin");

            if (!CreateFunction) {
                LOG_ERROR(boost::locale::translate("Could not find 'CreatePlugin' symbol in ").str() + Path + boost::locale::translate(". Error: ").str() + dlerror());
                dlclose(Handle);
                continue;
            }

            PluginInterface* plugin_instance = CreateFunction();

            if (!plugin_instance) {
                LOG_ERROR(boost::locale::translate("Plugin factory function returned null for ").str() + Path);
                dlclose(Handle);
                continue;
            }
            auto Serve = std::make_unique<FrameworkServices>();
            plugin_instance->Initialize(Serve.get());
            plugin_instance->Enable();

            LoadedPlugins_.push_back({
                std::shared_ptr<PluginInterface>(plugin_instance),
                Handle,
                Path,
                std::move(Serve)
            });
            LOG_INFO(boost::locale::translate("Successfully loaded plugin: ").str() + std::string(plugin_instance->Name()));
        }
    }
}

const std::vector<PluginInfo>& PluginManage::GetLoadedPlugins() const {
    return LoadedPlugins_;
}

PluginManage::~PluginManage() {
    LOG_INFO(boost::locale::translate("Uninstalling all plugins..."));
    for (auto& Plugins : LoadedPlugins_) {
        if (Plugins.Instance) {
            Plugins.Instance->Disable();
        }
        if (Plugins.Handle) {
            dlclose(Plugins.Handle);
        }
    }
    LoadedPlugins_.clear();
    LOG_INFO(boost::locale::translate("All plugins have been uninstalled."));
}