set(SRCS_V2
    main.cpp
    )
# add the executable
add_executable(CFD_Eigen_v2 ${SRCS_V2})
target_include_directories(CFD_Eigen_v2 PRIVATE ${EIGEN3_INCLUDE_DIR})