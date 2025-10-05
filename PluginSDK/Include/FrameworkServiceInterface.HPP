#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP

#include "LoggerInterface.HPP"

class FrameworkServiceInterface {
    public:
        virtual ~FrameworkServiceInterface() = default;
        virtual LoggerInterface* GetLogger() = 0;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICEINTERFACE_HPP