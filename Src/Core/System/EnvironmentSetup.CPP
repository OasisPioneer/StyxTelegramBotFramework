#include "Core/System/EnvironmentSetup.HPP"

#include <boost/dll/runtime_symbol_info.hpp>

bool EnvironmentSetup::EnsureDirectoryExist(const std::vector<std::string> &Subdirectory) {
    try {
        boost::filesystem::path BasicPath = boost::dll::program_location().parent_path();
        for (const std::string& Directory : Subdirectory) {
            if (Directory.empty()) {
                continue;
            }
            boost::filesystem::path FullPath = BasicPath / Directory;
            boost::filesystem::create_directories(FullPath);
        }
    } catch (const boost::filesystem::filesystem_error&) {
        return false;
    }
    return true;
}