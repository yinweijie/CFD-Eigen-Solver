cmake_minimum_required(VERSION 3.10)

# set the project name
project(CFD_Eigen)

include_directories(/usr/local/include/eigen3)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# add the executable
add_executable(CFD_Eigen ${DIR_SRCS})