#ifndef STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP
#define STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP

#include <atomic>
#include <string>
#include <vector>

class SystemStructure;

class Application {
    public:

        Application() = default;
        ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        bool Initialize();
        int Run();
        void Stop();

        bool RunningStatus() const {return Running_Status;}
    private:
        std::atomic<bool> Running_Status{false};
        std::vector<std::string> RequiredDirectories;
};

#endif //STYXTELEGRAMBOTFRAMEWORK_APPLICATION_HPP