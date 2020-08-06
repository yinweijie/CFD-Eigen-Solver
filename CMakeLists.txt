cmake_minimum_required(VERSION 3.10)

# set the project name
project(CFD_Eigen)

include_directories(/usr/local/include/eigen3)
# add the executable
add_executable(CFD_Eigen main.cpp Inputs.cpp Mesh.cpp MatrixCoeff.cpp)