set(SRCS_V3
    main.cpp
    )
# add the executable
add_executable(CFD_Eigen_v3 ${SRCS_V3})
target_include_directories(CFD_Eigen_v3 PRIVATE ${EIGEN3_INCLUDE_DIR})