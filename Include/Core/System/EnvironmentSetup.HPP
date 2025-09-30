#ifndef STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_HPP
#define STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_HPP

#include <string>
#include <vector>

class EnvironmentSetup {
    public:

        /**
         * @brief
         *   @if LANG_CN 获取跨平台的系统级配置文件目录路径。
         *   @endif
         *   @if LANG_EN Gets the cross-platform system-level configuration file directory path.
         *   @endif
         *
         * @details
         *   @if LANG_CN
         *     - 在 Windows 平台上，此函数返回 `%APPDATA%` 环境变量指向的路径。
         *     - 在 Linux 和 macOS 平台上，此函数遵循 XDG 基本目录规范，返回 `$HOME/.config` 路径。
         *     该函数的性能非常高，因为它主要依赖于读取环境变量，这是一个低开销的操作。
         *   @endif
         *   @if LANG_EN
         *     - On the Windows platform, this function returns the path pointed to by the `%APPDATA%` environment variable.
         *     - On Linux and macOS platforms, this function follows the XDG Base Directory Specification and returns the `$HOME/.config` path.
         *     The performance of this function is very high as it primarily relies on reading environment variables, which is a low-overhead operation.
         *   @endif
         *
         * @return
         *   @if LANG_CN
         *     返回一个 `std::string`，其中包含配置目录的绝对路径。
         *     如果无法确定路径（例如，所需的环境变量未设置），则返回一个空字符串。
         *   @endif
         *   @if LANG_EN
         *     Returns a `std::string` containing the absolute path to the configuration directory.
         *     If the path cannot be determined (e.g., the required environment variable is not set), it returns an empty string.
         *   @endif
         */
        static std::string GetSystemConfigPath();

        /**
        * @brief
        *   @if LANG_CN 确保目录存在。
        *   @endif
        *   @if LANG_EN Make sure the directory exists.
        *   @endif
        *
        * @param Subdirectory
        *   @if LANG_CN 文件夹名称数组。
        *   @endif
        *   @if LANG_EN Array of folder names.
        *   @endif
        * @return
        *   @if LANG_CN 如果存在/创建成功则返回真，否则为假。
        *   @endif
        *   @if LANG_EN Returns true if it exists or is created successfully, otherwise returns false.
        *   @endif
        */
        static bool EnsureDirectoryExist(const std::vector<std::string>& Subdirectory);
};

#endif //STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_HPP