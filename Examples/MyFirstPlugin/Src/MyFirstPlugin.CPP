#include "MyFirstPlugin.HPP"

const char* MyFirstPlugin::Initialize(FrameworkServiceInterface* Service) {

    if (Service) {
        this->Service_ = Service;
        this->Token_ = "114231:1111111111111111";
    }
    if (Service_ && Service_->GetLogger()) {
        Service_->GetLogger()->Info("MyFirstPlugin Initialized.");
    }
    return this->Token_.c_str();
}

const char *MyFirstPlugin::Token() const {
    return Token_.c_str();
}


void MyFirstPlugin::Enable() {
    if (Service_ && Service_->GetLogger()) {
        // 使用保存的服务指针来获取 Logger
        Service_->GetLogger()->Info("MyFirstPlugin Enabled!");
        // 你也可以在这里使用令牌
        Service_->GetLogger()->Info(("Token used: " + Token_).c_str());
    }
}

void MyFirstPlugin::Disable() {
    if (Service_ && Service_->GetLogger()) {
        Service_->GetLogger()->Info("MyFirstPlugin Disabled!");
    }
}

extern "C" PluginInterface* CreatePlugin() {
    return new MyFirstPlugin();
}