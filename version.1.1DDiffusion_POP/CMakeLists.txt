set(SRCS_V1
    main.cpp
    )
# add the executable
add_executable(CFD_Eigen_v1 ${SRCS_V1})
target_include_directories(CFD_Eigen_v1 PRIVATE ${EIGEN3_INCLUDE_DIR})