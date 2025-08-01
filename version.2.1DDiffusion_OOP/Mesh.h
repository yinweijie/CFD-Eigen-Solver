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
    // 网格数量
    int N;
    // 网格x方向面坐标
    VectorXd xFace;
    // 网格x方向中心坐标
    VectorXd xCentroid;
    // d_LP, d_PR：网格中心与左右相邻网格中心举例
    VectorXd d_LP, d_PR;
    // k*A/d
    VectorXd DA_L, DA_R;
    // 网格体积
    VectorXd V;

private:
    // 初始化网格
    void initMesh(double L, int N);
public:
    Mesh(double L, int N_)
    {
        N = N_;
        xFace = VectorXd(N + 1);
        xCentroid = VectorXd(N);
        d_LP = VectorXd(N);
        d_PR = VectorXd(N);
        DA_L = VectorXd(N);
        DA_R = VectorXd(N);
        V = VectorXd(N);

        initMesh(L, N);
    }

    const VectorXd& get_DA_L() const { return DA_L; }
    const VectorXd& get_DA_R() const { return DA_R; }
    const VectorXd& get_V() const { return V; }
    int get_N() const { return N; }
};

inline void Mesh::initMesh(double L, int N)
{
    using namespace Inputs;

    // x方向网格长度
    double dx = L / N;

    // 网格面x坐标
    for(int i = 0; i <= N; i++)
    {
        xFace[i] = dx * i;
    }
    // cout << xFace << endl;

    // 网格中心坐标
    for(int i = 0; i < N; i++)
    {
        xCentroid[i] = 0.5 * (xFace[i] + xFace[i+1]);
    }
    // cout << xCentroid << endl;

    // 网格中心相关量
    for(int i = 0; i < N; i++)
    {
        if(i == 0) // 左边界的d_LP需要特殊处理
        {
            d_LP[i] = 2 * (xCentroid[i] - xFace[i]);
            d_PR[i] = xCentroid[i+1] - xCentroid[i];
        }
        else if(i == N - 1) // 右边界的d_PR需要特殊处理
        {
            d_LP[i] = xCentroid[i] - xCentroid[i-1];
            d_PR[i] = 2 * (xFace[i+1] - xCentroid[i]);
        }
        else // 内点的d_LP, d_PR
        {
            d_LP[i] = xCentroid[i] - xCentroid[i-1];
            d_PR[i] = xCentroid[i+1] - xCentroid[i];
        }

        DA_L[i] = k * A / d_LP[i];
        DA_R[i] = k * A / d_PR[i];

        // 网格体积 = faceArea * dx
        V[i] = A * (xFace[i+1] - xFace[i]);
    }
}

#endif