#ifndef __INPUTS_H__
#define __INPUTS_H__

namespace Inputs
{
    // # Thermal Conductivity of the bar (W/mK)
    constexpr double k = 100;
    
    // # Cross-sectional Area of the bar (m2)
    constexpr double A = 0.1;
    
    // # Length of the bar (m)
    constexpr double L = 5;
    
    // # Number of cells in the mesh
    constexpr int N = 5;
    
    // # Temperature at the left hand side of the bar (deg C)
    constexpr double T_A = 100;
    
    // # Temperature at the left hand side of the bar (deg C)
    constexpr double T_B = 200;
    
    // # Heat source per unit volume (W/m3)
    constexpr double S_bar = 1000;
}

#endif