#include "Inputs.h"
    
Inputs::Inputs(const std::string& FileName)
{
    initInputs();
}

void Inputs::initInputs()
{
    // Thermal Conductivity of the bar (W/mK)
    k = 100;
    
    // Cross-sectional Area of the bar (m2)
    A = 0.1;

    L = 5;

    // 计算域X，Y，Z方向长度 (m)
    geometry.XLen = 5;
    geometry.YLen = 5;
    geometry.ZLen = 5;
    
    // Number of cells in the mesh
    N = 5;
    
    // Temperature at the left hand side of the bar (deg C)
    T_A = 100;
    
    // Temperature at the left hand side of the bar (deg C)
    T_B = 200;
    
    // Heat source per unit volume (W/m3)
    S_bar = 1000;

    // 密度 kg/m^3
    rho = 1.0;

    // 比热容 J/kg/k
    cp = 1000;

    // 流体速度
    U = 0.0;

    // 左边界热流密度 (W/m^2)
    q_w = 100;
}