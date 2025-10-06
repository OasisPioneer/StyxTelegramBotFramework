#ifndef STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP

#include "FrameworkServiceInterface.HPP"

class PluginInterface {
    public:
        virtual ~PluginInterface() = default;
        virtual const char* Initialize(FrameworkServiceInterface* Service) = 0;

        virtual const char* Name() const = 0;
        virtual const char* Version() const = 0;
        virtual const char* Author() const = 0;
        virtual const char* Description() const = 0;

        virtual void Enable() = 0;
        virtual void Disable() = 0;
};

extern "C" {
    typedef PluginInterface* (*CreatePluginFunction)();
    PluginInterface* CreatePlugin();
}

#endif //STYXTELEGRAMBOTFRAMEWORK_PLUGININTERFACE_HPP