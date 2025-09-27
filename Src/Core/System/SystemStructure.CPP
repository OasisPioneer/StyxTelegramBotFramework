#include "Core/System/SystemStructure.HPP"

#include <boost/filesystem.hpp>

bool SystemStructure::CheckCreateDirectory(const std::string &Directory) {
    try {
        if (!boost::filesystem::exists(Directory)) {
            bool Create = boost::filesystem::create_directories(Directory);
            if (Create) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } catch (...) {
        return false;
    }
}
