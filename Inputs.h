#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <string>

class InputReader
{
public:
    InputReader(const std::string& fileName)
    {
        // To do ...
        // 读取Inputs.dat中数据，给namespace Inputs中数据赋值
    }
};

namespace Inputs
{
    // # Thermal Conductivity of the bar (W/mK)
    double k = 100;
    
    // # Cross-sectional Area of the bar (m2)
    double A = 0.1;
    
    // # Length of the bar (m)
    double L = 5;
    
    // # Number of cells in the mesh
    int N = 5;
    
    // # Temperature at the left hand side of the bar (deg C)
    double T_A = 100;
    
    // # Temperature at the left hand side of the bar (deg C)
    double T_B = 200;
    
    // # Heat source per unit volume (W/m3)
    double S_bar = 1000;

    // 密度 kg/m^3
    double rho = 1.0;

    // 比热容 J/kg/k
    double cp = 1000;

    // 流体速度
    double U = 0.0;

    // 左边界热流密度 (W/m^2)
    double q_w = 100;
}

#endif