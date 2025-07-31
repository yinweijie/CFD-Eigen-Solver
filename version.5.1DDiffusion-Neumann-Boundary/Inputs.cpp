#include "Inputs.h"


// 实现文件中的定义（需要在.cpp文件中或者在头文件中inline定义）
namespace Inputs
{
    double k = 100.0;
    double A = 0.1;
    double L = 5.0;
    int N = 5;
    double T_A = 100.0;
    double T_B = 200.0;
    double S_bar = 1000.0;
    double rho = 1.0;
    double cp = 1000.0;
    double U = 0.0;
    double q_w = 100.0;
}

void InputReader::loadInputs()
{
    // 读取JSON配置并赋值，提供默认值防止键不存在
    Inputs::k = config.value("thermal_conductivity", 100.0);
    Inputs::A = config.value("cross_sectional_area", 0.1);
    Inputs::L = config.value("length", 5.0);
    Inputs::N = config.value("number_of_cells", 5);
    Inputs::T_A = config.value("temperature_left", 100.0);
    Inputs::T_B = config.value("temperature_right", 200.0);
    Inputs::S_bar = config.value("heat_source", 1000.0);
    Inputs::rho = config.value("density", 1.0);
    Inputs::cp = config.value("specific_heat", 1000.0);
    Inputs::U = config.value("fluid_velocity", 0.0);
    Inputs::q_w = config.value("heat_flux_boundary", 100.0);
    
    // 输出读取的配置信息
    std::cout << "--------------------------------" << std::endl;
    std::cout << "配置读取:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "热导率: " << Inputs::k << " W/mK" << std::endl;
    std::cout << "截面积: " << Inputs::A << " m²" << std::endl;
    std::cout << "长度: " << Inputs::L << " m" << std::endl;
    std::cout << "网格数: " << Inputs::N << std::endl;
    std::cout << "左端温度: " << Inputs::T_A << " °C" << std::endl;
    std::cout << "右端温度: " << Inputs::T_B << " °C" << std::endl;
    std::cout << "单位体积热源: " << Inputs::S_bar << " W/m³" << std::endl;
    std::cout << "密度: " << Inputs::rho << " kg/m³" << std::endl;
    std::cout << "比热容: " << Inputs::cp << " J/kg/K" << std::endl;
    std::cout << "流体速度: " << Inputs::U << " m/s" << std::endl;
    std::cout << "左边界热流密度: " << Inputs::q_w << " W/m²" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "配置文件加载成功。" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << std::endl;
}