set(SRCS_V5
    main.cpp
    Inputs.cpp
    )
# add the executable
add_executable(CFD_Eigen_v5 ${SRCS_V5})
target_include_directories(CFD_Eigen_v5 PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(CFD_Eigen_v5 PRIVATE nlohmann_json::nlohmann_json)