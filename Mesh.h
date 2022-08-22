#ifndef __MESH_H__
#define __MESH_H__

#include <Eigen/Dense>
#include "Inputs.h"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::VectorXi;

class Mesh
{
private:
    // x, y, z方向，面坐标
    VectorXd xFace, yFace, zFace;
    // 网格x, y, z方向中心坐标
    VectorXd xCentroid, yCentroid, zCentroid;
    // 网格中心与左/右/下/上，相邻网格中心距离
    VectorXd d_LP, d_PR, d_BP, d_PT;
    // 标记是否已被赋值，0未赋值，1已赋值
    VectorXi flag_d_LP, flag_d_PR, flag_d_BP, flag_d_PT;
    // 网格体积
    VectorXd V;
    // 网格数量
    int Nx, Ny, Nz, N;
    // 网格横截面积
    double Ax, Ay, Az;
    // 网格长度
    double dx, dy, dz;

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

        flag_d_LP = VectorXi::Zero(N);
        flag_d_PR = VectorXi::Zero(N);
        flag_d_BP = VectorXi::Zero(N);
        flag_d_PT = VectorXi::Zero(N);

        V = VectorXd(N);

        initMesh(inputs);
    }

    const VectorXd& get_V() const { return V; }

    const VectorXd& get_d_LP() const { return d_LP; }
    const VectorXd& get_d_PR() const { return d_PR; }
    const VectorXd& get_d_BP() const { return d_BP; }
    const VectorXd& get_d_PT() const { return d_PT; }

    int get_N() const { return N; }

    double get_Ax() const { return Ax; }
    double get_Ay() const { return Ay; }
    double get_Az() const { return Az; }

    double get_dx() const { return dx; }
    double get_dy() const { return dy; }
    double get_dz() const { return dz; }

    // 判断网格是否紧邻边界
    bool is_at_left_boundary(int global_index) const { return ((global_index % Nx) == 0); }
    bool is_at_right_boundary(int global_index) const { return ((global_index % Nx) == Nx - 1); }
    bool is_at_bottom_boundary(int global_index) const { return ((global_index / Nx) == 0); }
    bool is_at_top_boundary(int global_index) const { return ((global_index / Nx) == Ny - 1); }
    bool is_at_front_boundary(int global_index) const { return ((global_index / (Nx * Ny)) == 0); }
    bool is_at_back_boundary(int global_index) const { return ((global_index / (Nx * Ny)) == Nz - 1); }

    // 返回当前网格 左/右/下/上 的全局编号
    int left_of(int global_index) const { return (global_index - 1); }
    int right_of(int global_index) const { return (global_index + 1); }
    int bottom_of(int global_index) const { return (global_index - Nx); }
    int top_of(int global_index) const { return (global_index + Nx); }

    const VectorXd& get_xCentroid() const { return xCentroid; }
    const VectorXd& get_yCentroid() const { return yCentroid; }
    const VectorXd& get_zCentroid() const { return zCentroid; }

    const VectorXd& get_xFace() const { return xFace; }
    const VectorXd& get_yFace() const { return yFace; }
    const VectorXd& get_zFace() const { return zFace; }

    int ix_of(int global_index) const { return (global_index % Nx); }
    int iy_of(int global_index) const { return (global_index / Nx); }
    int iz_of(int global_index) const { return (global_index / (Nx * Ny)); }
};

#endif