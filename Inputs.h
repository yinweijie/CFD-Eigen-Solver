#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <string>

struct Geometry
{
    double XLen;
    double YLen;
    double ZLen;
};

class Inputs
{
public:
    // Thermal Conductivity of the bar (W/mK)
    double k;
    
    // Cross-sectional Area of the bar (m2)
    double A;

    double L;

    // 计算域X，Y，Z方向长度 (m)
    Geometry geometry;
    
    // Number of cells in the mesh
    int N;
    
    // Temperature at the left hand side of the bar (deg C)
    double T_A;
    
    // Temperature at the left hand side of the bar (deg C)
    double T_B;
    
    // Heat source per unit volume (W/m3)
    double S_bar;

    // 密度 kg/m^3
    double rho;

    // 比热容 J/kg/k
    double cp;

    // 流体速度
    double U;

    // 左边界热流密度 (W/m^2)
    double q_w;

public:
    // To do ...
    // 读取Inputs.dat中数据，给namespace Inputs中数据赋值
    Inputs(const std::string& FileName);

    void initInputs();
};

// namespace Inputs
// {
//     // Thermal Conductivity of the bar (W/mK)
//     double k;
    
//     // Cross-sectional Area of the bar (m2)
//     double A;

//     double L;

//     // 计算域X，Y，Z方向长度 (m)
//     Geometry geometry;
    
//     // Number of cells in the mesh
//     int N;
    
//     // Temperature at the left hand side of the bar (deg C)
//     double T_A;
    
//     // Temperature at the left hand side of the bar (deg C)
//     double T_B;
    
//     // Heat source per unit volume (W/m3)
//     double S_bar;

//     // 密度 kg/m^3
//     double rho;

//     // 比热容 J/kg/k
//     double cp;

//     // 流体速度
//     double U;

//     // 左边界热流密度 (W/m^2)
//     double q_w;
// }

#endif