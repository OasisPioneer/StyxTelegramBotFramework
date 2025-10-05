#include "MyFirstPlugin.HPP"

void MyFirstPlugin::Initialize(FrameworkServiceInterface* Service) {
    if (Service) {
        this->Logger_ = Service->GetLogger();
    }
}

void MyFirstPlugin::Enable() {
    if (Logger_) {
        Logger_->Info("MyFirstPlugin Enabled!");
    }
}

void MyFirstPlugin::Disable() {
    if (Logger_) {
        Logger_->Info("MyFirstPlugin Disabled!");
    }
}

extern "C" PluginInterface* CreatePlugin() {
    return new MyFirstPlugin();
}

// extern "C" __attribute__((visibility("default"))) PluginInterface* create_plugin() {
//     return new MyFirstPlugin();
// }