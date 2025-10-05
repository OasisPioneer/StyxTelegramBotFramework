#ifndef STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP
#define STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP

#include "PluginInterface.HPP"

class MyFirstPlugin : public PluginInterface {
public:
    void Initialize(FrameworkServiceInterface* Service) override;
    const char* Name() const override { return "我的第一个插件"; }
    const char* Version() const override { return "1.0.0"; }
    const char* Author() const override { return "龙森"; }
    const char* Description() const override { return "A simple plugin to test the loading mechanism."; }

    void Enable() override;
    void Disable() override;
private:
    LoggerInterface* Logger_ = nullptr;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP