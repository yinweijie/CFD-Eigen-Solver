set(SRCS_V4
    main.cpp
    )
# add the executable
add_executable(CFD_Eigen_v4 ${SRCS_V4})
target_include_directories(CFD_Eigen_v4 PRIVATE ${EIGEN3_INCLUDE_DIR})