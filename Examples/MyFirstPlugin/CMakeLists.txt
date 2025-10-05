cmake_minimum_required(VERSION 3.15)
project(MyFirstPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 计算相对路径，现在这是安全可靠的
get_filename_component(FRAMEWORK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." REALPATH)

add_library(MyFirstPlugin SHARED
        Src/MyFirstPlugin.CPP # 假设你的文件名是大写的，如果不是请改为小写 .cpp
)

target_include_directories(MyFirstPlugin PUBLIC
        # 插件自己的 'src' 目录
        "${CMAKE_CURRENT_LIST_DIR}/Src"

        # SDK 的 include 目录
        "${FRAMEWORK_ROOT}/PluginSDK/Include"
)

set_target_properties(MyFirstPlugin PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Plugins"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Plugins"
)

set_target_properties(MyFirstPlugin PROPERTIES PREFIX "lib")
