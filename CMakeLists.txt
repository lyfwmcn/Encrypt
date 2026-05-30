# 最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 项目名（会自动变成 exe 名字）
project(Encrypt)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 递归搜索 src 下所有 .cpp 文件
file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.cc
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# 自动包含 src 下所有头文件目录（递归）
include_directories(${PROJECT_SOURCE_DIR}/src)

# 设置可执行文件输出目录 = 项目根目录 /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件（exe 名字 = 项目名）
add_executable(${PROJECT_NAME} ${SRC_FILES})