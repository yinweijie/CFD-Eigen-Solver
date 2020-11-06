#include "Inputs.h"
    
Inputs::Inputs(const std::string& FileName)
{
    initInputs();
}

void Inputs::initInputs()
{
    // Number of cells in the mesh
    Nx = 25;
    Ny = 25;
    Nz = 1;

    // 计算域X，Y，Z方向长度 (m)
    geometry.XLen = 1;
    geometry.YLen = 1;
    geometry.ZLen = 1;

    // Thermal Conductivity of the bar (W/mK)
    physcial_properties.k = 100;
    // 密度 kg/m^3
    physcial_properties.rho = 1.0;
    // 比热容 J/kg/k
    physcial_properties.cp = 1000;
    // 动力粘度 kg/(m.s)
    physcial_properties.mu = 0.01;
    
    // Temperature at the left boundary (deg C)
    boundary.T_left = 100;
    // Temperature at the right boundary (deg C)
    boundary.T_right = 200;
    // Temperature at the bottom boundary (deg C)
    boundary.T_bottom = 250;
    // Temperature at the top boundary (deg C)
    boundary.T_top = 150;
    // 左边界热流密度 (W/m^2)
    boundary.q_w = 100;

    boundary.U_left = 0.0;
    boundary.U_right = 0.0;
    boundary.U_top = 0.01;
    boundary.U_bottom = 0.0;

    boundary.V_left = 0.0;
    boundary.V_right = 0.0;
    boundary.V_top = 0.0;
    boundary.V_bottom = 0.0;

    boundary.p_left = 0.0;
    boundary.p_right = 0.0;
    boundary.p_top = 0.0;
    boundary.p_bottom = 0.0;

    // Heat source per unit volume (W/m3)
    source.S_bar = 1000;
}