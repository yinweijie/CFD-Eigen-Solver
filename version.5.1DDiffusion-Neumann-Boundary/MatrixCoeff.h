#ifndef __MATRIX_COEFF__
#define __MATRIX_COEFF__

#include <iostream>
#include "Inputs.h"
#include "Mesh.h"

using namespace std;

// N: 网格数
class MatrixCoeff
{
private:
    VectorXd aL, aR, aP, Sp, Su;

    MatrixXd A_m;
    VectorXd b_m;
    VectorXd x;

private:
// Matrix系数初始化
void initMatrix(const Mesh* mesh);

public:
    MatrixCoeff(const Mesh* mesh)
    {
        int N = mesh->get_N();

        aL = VectorXd(N);
        aR = VectorXd(N);
        aP = VectorXd(N);
        Sp = VectorXd(N);
        Su = VectorXd(N);

        A_m = MatrixXd(N, N);
        b_m = VectorXd(N);
        x = VectorXd (N);
        
        initMatrix(mesh);
    }

    MatrixXd& get_A_m() { return A_m; }
    VectorXd& get_b_m() { return b_m; }
    VectorXd& get_x() { return x; }
};

// a_{p} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
inline void MatrixCoeff::initMatrix(const Mesh* mesh)
{
    using namespace Inputs;

    const VectorXd& DA_L = mesh->get_DA_L();
    const VectorXd& DA_R = mesh->get_DA_R();
    const VectorXd& F_l = mesh->get_F_l();
    const VectorXd& F_r = mesh->get_F_r();
    const VectorXd& V = mesh->get_V();
    int N = mesh->get_N();

    aL = DA_L + F_l.cwiseMax(VectorXd::Zero(N));
    aL[0] = 0; // 左边界系数

    aR = DA_R + (-F_r).cwiseMax(VectorXd::Zero(N));
    aR[N-1] = 0; // 右边界系数

    Sp = VectorXd::Zero(N);
    // 黎曼边界不会引入Sp
    // Sp[0] = -(2*DA_L[0] + max(F_l[0], 0.0)); // 左边界引入系数矩阵的不规则项
    // Sp[N-1] = -(2*DA_R[N-1] + max(-F_r[0], 0.0)); // 右边界引入系数矩阵的不规则项 

    aP = aL + aR - Sp + (F_r - F_l);

    Su = S_bar * V;
    Su[0] = /*T_A*(2*DA_L[0] + max(F_l[0], 0.0))*/-q_w*A  + S_bar * V[0]; // 左边界使用黎曼边界条件
    Su[N-1] = T_B*(2*DA_R[N-1] + max(-F_r[N-1], 0.0)) + S_bar * V[N-1]; // 右边界用狄拉克边界条件

    for(int i = 0; i < N; i++)
    {
        if(i == 0)
        {
            A_m(i, i) = aP[i];
            A_m(i, i+1) = -aR[i];
        }
        else if(i == N-1)
        {
            A_m(i, i) = aP[i];
            A_m(i, i-1) = -aL[i];
        }
        else
        {
            A_m(i, i) = aP[i];
            A_m(i, i-1) = -aL[i];
            A_m(i, i+1) = -aR[i];
        }
    }

    b_m = Su;

    cout << "A_m: " << endl << A_m << endl;
    cout << endl;

    cout << "b_m: " << endl << b_m << endl;
    cout << endl;
}

#endif