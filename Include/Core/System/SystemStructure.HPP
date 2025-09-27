#ifndef STYXTELEGRAMBOTFRAMEWORK_SYSTEMSTRUCTURE_HPP
#define STYXTELEGRAMBOTFRAMEWORK_SYSTEMSTRUCTURE_HPP

#include <string>
#include <vector>

class SystemStructure {
    public:
        static bool CheckCreateDirectory(const std::string& Directory);
        std::vector<std::string> DirectoryArray = {"CachedData", "Plugins"};
};

#endif //STYXTELEGRAMBOTFRAMEWORK_SYSTEMSTRUCTURE_HPP