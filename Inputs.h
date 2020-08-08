#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <string>

struct Geometry
{
    // 计算域X，Y，Z方向长度 (m)
    double XLen;
    double YLen;
    double ZLen;
};

struct PhysicalPropterties
{
    // Thermal Conductivity of the bar (W/mK)
    double k;
    // 密度 kg/m^3
    double rho;
    // 比热容 J/kg/k
    double cp;
};

struct Boundary
{
    // Temperature at the left boundary (deg C)
    double T_left;
    // Temperature at the right boundary (deg C)
    double T_right;
    // Temperature at the bottom boundary (deg C)
    double T_bottom;
    // Temperature at the top boundary (deg C)
    double T_top;
    // 左边界热流密度 (W/m^2)
    double q_w;
    // 流体速度
    double U;
};

struct Source
{
    // Heat source per unit volume (W/m3)
    double S_bar;
};

class Inputs
{
public:
    
    // Number of cells in the mesh
    int Nx, Ny, Nz;

    Geometry geometry;

    // 物性
    PhysicalPropterties physcial_properties;

    // 边界
    Boundary boundary;

    // 源项
    Source source;

public:
    // To do ...
    // 读取Inputs.dat中数据，给Inputs中数据赋值
    Inputs(const std::string& FileName);

    void initInputs();
};

#endif