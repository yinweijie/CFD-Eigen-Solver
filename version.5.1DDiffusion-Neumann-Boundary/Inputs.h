#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class InputReader
{
private:
    json config;
    
public:
    InputReader(const std::string& fileName)
    {
        try {
            std::ifstream file(fileName);
            if (!file.is_open()) {
                throw std::runtime_error("无法打开配置文件: " + fileName);
            }
            
            file >> config;
            file.close();
            
            // 读取配置并赋值给Inputs命名空间
            loadInputs();
            
        } catch (const std::exception& e) {
            std::cerr << "读取配置文件错误: " << e.what() << std::endl;
            throw;
        }
    }
    
private:
    void loadInputs();
};

namespace Inputs
{
    // Thermal Conductivity of the bar (W/mK)
    extern double k;
    
    // Cross-sectional Area of the bar (m2)
    extern double A;
    
    // Length of the bar (m)
    extern double L;
    
    // Number of cells in the mesh
    extern int N;
    
    // Temperature at the left hand side of the bar (deg C)
    extern double T_A;
    
    // Temperature at the right hand side of the bar (deg C)
    extern double T_B;
    
    // Heat source per unit volume (W/m3)
    extern double S_bar;

    // 密度 kg/m^3
    extern double rho;

    // 比热容 J/kg/k
    extern double cp;

    // 流体速度
    extern double U;

    // 左边界热流密度 (W/m^2)
    extern double q_w;
}

#endif