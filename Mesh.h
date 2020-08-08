#ifndef __MESH_H__
#define __MESH_H__

#include <Eigen/Dense>
#include "Inputs.h"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Mesh
{
private:
    // x, y, z方向，面坐标
    VectorXd xFace, yFace, zFace;
    // 网格x, y, z方向中心坐标
    VectorXd xCentroid, yCentroid, zCentroid;
    // 网格中心与左/右/下/上，相邻网格中心距离
    VectorXd d_LP, d_PR, d_BP, d_PT;
    // k*A/d
    VectorXd DA_L, DA_R, DA_B, DA_T;
    // F = rho * cp * U * A
    VectorXd F_l, F_r;
    // 网格左/右面速度
    VectorXd U_l, U_r;
    // 网格体积
    VectorXd V;
    // 网格数量
    int Nx, Ny, Nz, N;
    // 网格横截面积
    double Ax, Ay, Az;
private:
    // 初始化网格
    void initMesh(const Inputs* inputs);
public:
    Mesh(const Inputs* inputs) : Nx(inputs->Nx), Ny(inputs->Ny), Nz(inputs->Nz), N(Nx*Ny*Nz)
    {
        xFace = VectorXd(Nx + 1);
        yFace = VectorXd(Ny + 1);
        zFace = VectorXd(Nz + 1);

        xCentroid = VectorXd(N);
        yCentroid = VectorXd(N);
        zCentroid = VectorXd(N);

        d_LP = VectorXd(N);
        d_PR = VectorXd(N);
        d_BP = VectorXd(N);
        d_PT = VectorXd(N);

        DA_L = VectorXd(N);
        DA_R = VectorXd(N);
        DA_B = VectorXd(N);
        DA_T = VectorXd(N);

        F_l = VectorXd(N);
        F_r = VectorXd(N);

        U_l = VectorXd(N);
        U_r = VectorXd(N);

        V = VectorXd(N);

        initMesh(inputs);
    }

    const VectorXd& get_DA_L() const { return DA_L; }
    const VectorXd& get_DA_R() const { return DA_R; }
    const VectorXd& get_DA_B() const { return DA_B; }
    const VectorXd& get_DA_T() const { return DA_T; }

    const VectorXd& get_F_l() const { return F_l; }
    const VectorXd& get_F_r() const { return F_r; }

    const VectorXd& get_V() const { return V; }

    int get_N() const { return N; }

    double get_Ax() const { return Ax; }
    double get_Ay() const { return Ay; }
    double get_Az() const { return Az; }
};

#endif