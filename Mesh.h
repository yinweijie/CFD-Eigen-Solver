#ifndef __MESH_H__
#define __MESH_H__

#include <Eigen/Dense>
#include "Inputs.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

// N: 网格数
// L: 计算域长度
class Mesh
{
private:
    // 网格x方向面坐标
    VectorXd xFace;
    // 网格x方向中心坐标
    VectorXd xCentroid;
    // d_LP, d_PR：网格中心与左右相邻网格中心举例
    VectorXd d_LP, d_PR;
    // k*A/d
    VectorXd DA_L, DA_R;
    // F = rho * cp * U * A
    VectorXd F_l, F_r;
    // 网格左/右面速度
    VectorXd U_l, U_r;
    // 网格体积
    VectorXd V;
    // 网格数量
    int N;
private:
    // 初始化网格
    void initMesh(const Inputs* inputs);
public:
    Mesh(const Inputs* inputs) : N(inputs->N)
    {
        xFace = VectorXd(N + 1);
        xCentroid = VectorXd(N);
        d_LP = VectorXd(N);
        d_PR = VectorXd(N);
        DA_L = VectorXd(N);
        DA_R = VectorXd(N);
        F_l = VectorXd(N);
        F_r = VectorXd(N);
        U_l = VectorXd(N);
        U_r = VectorXd(N);
        V = VectorXd(N);

        initMesh(inputs);
    }

    const VectorXd& get_DA_L() const { return DA_L; }
    const VectorXd& get_DA_R() const { return DA_R; }
    const VectorXd& get_F_l() const { return F_l; }
    const VectorXd& get_F_r() const { return F_r; }
    const VectorXd& get_V() const { return V; }
    int get_N() const { return N; }
};

#endif