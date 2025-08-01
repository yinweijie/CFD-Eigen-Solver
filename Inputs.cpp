#include "Inputs.h"
#include <fstream>
#include <iostream>
    
Inputs::Inputs(const std::string& fileName)
{
    try {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::runtime_error("无法打开配置文件: " + fileName);
        }
        
        file >> config;
        file.close();
        
        // 读取配置并赋值
        loadInputs();
        
    } catch (const std::exception& e) {
        std::cerr << "读取配置文件错误: " << e.what() << std::endl;
        throw;
    }
}

void Inputs::loadInputs()
{
    // 提取几何参数
    if (config.contains("geometry")) {
        auto geom = config["geometry"];
        geometry.Nx = geom.value("Nx", 50);  // 从JSON中读取，默认值50
        geometry.Ny = geom.value("Ny", 25);  // 从JSON中读取，默认值25
        geometry.Nz = geom.value("Nz", 1);   // 从JSON中读取，默认值1
        geometry.XLen = geom.value("XLen", 1.0);
        geometry.YLen = geom.value("YLen", 1.0);
        geometry.ZLen = geom.value("ZLen", 1.0);
    }

    // 提取物理属性
    if (config.contains("physcial_properties")) {
        auto props = config["physcial_properties"];
        physcial_properties.k = props.value("k", 100.0);
        physcial_properties.rho = props.value("rho", 1.0);
        physcial_properties.cp = props.value("cp", 1000.0);
        physcial_properties.mu = props.value("mu", 0.01);
    }

    // 提取边界条件
    if (config.contains("boundary")) {
        auto bound = config["boundary"];
        boundary.T_left = bound.value("T_left", 100.0);
        boundary.T_right = bound.value("T_right", 200.0);
        boundary.T_bottom = bound.value("T_bottom", 250.0);
        boundary.T_top = bound.value("T_top", 150.0);
        boundary.q_w = bound.value("q_w", 100.0);
        
        boundary.U_left = bound.value("U_left", 0.0);
        boundary.U_right = bound.value("U_right", 0.0);
        boundary.U_top = bound.value("U_top", 0.01);
        boundary.U_bottom = bound.value("U_bottom", 0.0);
        
        boundary.V_left = bound.value("V_left", 0.0);
        boundary.V_right = bound.value("V_right", 0.0);
        boundary.V_top = bound.value("V_top", 0.0);
        boundary.V_bottom = bound.value("V_bottom", 0.0);
        
        boundary.p_left = bound.value("p_left", 0.0);
        boundary.p_right = bound.value("p_right", 0.0);
        boundary.p_top = bound.value("p_top", 0.0);
        boundary.p_bottom = bound.value("p_bottom", 0.0);
    }

    // 提取源项
    if (config.contains("source")) {
        auto src = config["source"];
        source.S_bar = src.value("S_bar", 1000.0);
    }
    
    // 输出读取的配置信息以验证
    std::cout << "配置读取完成:" << std::endl;
    std::cout << "网格尺寸: " << geometry.Nx << "x" << geometry.Ny << "x" << geometry.Nz << std::endl;
    std::cout << "计算域尺寸: " << geometry.XLen << "x" << geometry.YLen << "x" << geometry.ZLen << std::endl;
    std::cout << "热导率: " << physcial_properties.k << " W/mK" << std::endl;
    std::cout << "左边界温度: " << boundary.T_left << " °C" << std::endl;
}