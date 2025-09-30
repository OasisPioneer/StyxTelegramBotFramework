#include "Core/System/EnvironmentSetup.HPP"

#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/dll/runtime_symbol_info.hpp>

std::string EnvironmentSetup::GetSystemConfigPath() {
    boost::filesystem::path SystemConfigPath;
    #ifdef _WIN32
        const char* APPDATA = std::getenv("APPDATA");
        if (APPDATA) {
            SystemConfigPath = APPDATA;
        }
    #elif defined(__linux__) || defined(__APPLE__)
        const char* HOME = std::getenv("HOME");
        if (HOME) {
            SystemConfigPath = HOME;
            SystemConfigPath /= ".config";
        }
    #endif
        if (SystemConfigPath.empty()) {
            return "";
        }
    return SystemConfigPath.string();
}

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