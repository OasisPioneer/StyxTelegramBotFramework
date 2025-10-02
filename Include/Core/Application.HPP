#ifndef STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP
#define STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP

#include <atomic>
#include <memory>

class Application {
    public:

        Application();
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        bool Initialize();
        void Start();

    private:
        std::atomic<bool> RunningStatus;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP