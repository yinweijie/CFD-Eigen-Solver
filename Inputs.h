#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <string>
#include <nlohmann/json.hpp>

struct Geometry
{
    // 计算域X，Y，Z方向长度 (m)
    double XLen;
    double YLen;
    double ZLen;
    int Nx;
    int Ny;
    int Nz;
};

struct PhysicalPropterties
{
    // Thermal Conductivity of the bar (W/mK)
    double k;
    // 密度 kg/m^3
    double rho;
    // 比热容 J/kg/k
    double cp;
    // 动力粘度 kg/(m.s)
    double mu;
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

    double U_left;
    double U_right;
    double U_top;
    double U_bottom;

    double V_left;
    double V_right;
    double V_top;
    double V_bottom;

    double p_left;
    double p_right;
    double p_top;
    double p_bottom;
};

struct Source
{
    // Heat source per unit volume (W/m3)
    double S_bar;
};

class Inputs
{
public:
    
    Geometry geometry;

    // 物性
    PhysicalPropterties physcial_properties;

    // 边界
    Boundary boundary;

    // 源项
    Source source;

public:
    Inputs(const std::string& fileName);

    void loadInputs();

private:
    nlohmann::json config;
};

#endif