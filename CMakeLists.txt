cmake_minimum_required(VERSION 3.10)

# set the project name
project(CFD_Eigen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 关闭Eigen中的这条警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy")
# 关闭unused变量警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")

# lib eigen337
list(APPEND CMAKE_PREFIX_PATH "lib_eigen337") # 安装路径前缀
find_package(Eigen3 REQUIRED)

if (EIGEN3_FOUND)
    message(STATUS "Found Eigen3")
    message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")
endif()

# lib nlohmann_json
list(APPEND CMAKE_PREFIX_PATH "lib_json") # 安装路径前缀
find_package(nlohmann_json 3.12.0 REQUIRED)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

add_subdirectory("version.1.1DDiffusion_POP")

add_subdirectory("version.2.1DDiffusion_OOP")

add_subdirectory("version.3.1DDiffusion-Convection")

add_subdirectory("version.4.1DDiffusion-Convection-Upwind")

add_subdirectory("version.5.1DDiffusion-Neumann-Boundary")

# add the executable
add_executable(CFD_Eigen ${DIR_SRCS})
target_include_directories(CFD_Eigen PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(CFD_Eigen PRIVATE nlohmann_json::nlohmann_json)
target_compile_options(CFD_Eigen PRIVATE -Wall -Wextra -Werror)