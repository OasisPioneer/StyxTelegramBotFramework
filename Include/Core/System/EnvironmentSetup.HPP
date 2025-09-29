#ifndef STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_HPP
#define STYXTELEGRAMBOTFRAMEWORK_ENVIRONMENTSETUP_HPP

#include <string>
#include <vector>

class EnvironmentSetup {
    public:

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