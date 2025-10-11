#ifndef STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP
#define STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP

#include "PluginInterface.HPP"

#include <string>
#include <vector>

class MyFirstPlugin : public PluginInterface {
public:
    const char* Initialize(FrameworkServiceInterface* Service) override;
    const char* Token() const override;
    const char* Name() const override { return "我的第一个插件"; }
    const char* Version() const override { return "1.0.0"; }
    const char* Author() const override { return "龙森"; }
    const char* Description() const override { return "A simple plugin to test the loading mechanism."; }

    void Enable() override;
    void Disable() override;
    
    // 事件处理方法
    void OnMessage(const Telegram::Message& message) override;
    void OnCallbackQuery(const Telegram::CallbackQuery& query) override;
    void OnCommand(const std::string& command, const Telegram::Message& message) override;
    std::vector<std::string> GetSupportedCommands() const override;
private:
    FrameworkServiceInterface* Service_ = nullptr;
    std::string Token_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_MYFIRSTPLUGIN_HPP