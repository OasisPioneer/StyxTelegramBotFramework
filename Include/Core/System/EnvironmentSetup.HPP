#ifndef STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_H
#define STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_H

#include <string>
#include <vector>

class EnvironmentSetup {
    public:
        static bool EnsureDirectoryExist(const std::vector<std::string>& Subdirectory);
};

#endif //STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_H