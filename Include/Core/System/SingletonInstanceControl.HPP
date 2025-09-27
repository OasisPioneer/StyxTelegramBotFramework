#ifndef STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP
#define STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP

#include <string>
#include <memory>

class SingletonInstanceControlIMPL;

class SingletonInstanceControl {
    public:
        explicit SingletonInstanceControl(const std::string& InstanceID);
        ~SingletonInstanceControl();

        SingletonInstanceControl(SingletonInstanceControl const&) = delete;
        SingletonInstanceControl& operator=(SingletonInstanceControl const&) = delete;
        SingletonInstanceControl(SingletonInstanceControl&&) = delete;
        SingletonInstanceControl& operator=(SingletonInstanceControl&&) = delete;

    private:
    std::unique_ptr<SingletonInstanceControlIMPL> PIMPL;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_SINGLETONINSTANCECONTROL_HPP