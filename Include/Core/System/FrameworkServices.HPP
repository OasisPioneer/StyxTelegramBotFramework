#ifndef STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP
#define STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP

#include "FrameworkServiceInterface.HPP"
#include "FrameworkLogger.HPP"

#include <memory>

class FrameworkServices : public FrameworkServiceInterface {
    public:
        FrameworkServices() : Logger_(std::make_unique<FrameworkLogger>()){}
        LoggerInterface* GetLogger() override {
            return Logger_.get();
        }
    private:
        std::unique_ptr<FrameworkLogger> Logger_;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_FRAMEWORKSERVICES_HPP