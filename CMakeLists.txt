cmake_minimum_required(VERSION 3.10)

# set the project name
project(CFD_Eigen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include_directories(/usr/local/include/eigen3)
list(APPEND CMAKE_PREFIX_PATH "lib_eigen337") # 安装路径前缀
find_package(Eigen3 REQUIRED)

if (EIGEN3_FOUND)
    message(STATUS "Found Eigen3")
    message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# add the executable
add_executable(CFD_Eigen ${DIR_SRCS})
target_include_directories(CFD_Eigen PRIVATE ${EIGEN3_INCLUDE_DIR})