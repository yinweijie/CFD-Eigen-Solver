#include "MatrixCoeff.h"

// a_{p} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
void MatrixCoeff::initMatrix(const Mesh* mesh, const Boundary& boundary, const Source& source)
{
    int N = mesh->get_N();

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

MatrixCoeff& MatrixCoeff::addConvectionTerm(const Mesh* mesh, const Boundary& boundary, const Source& source)
{
    double T_l = boundary.T_left;
    double T_r = boundary.T_right;
    double T_b = boundary.T_bottom;
    double T_t = boundary.T_top;
    double q_w = boundary.q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    const VectorXd& F_l = mesh->get_F_l();
    const VectorXd& F_r = mesh->get_F_r();

    int N = mesh->get_N();

    aL += F_l.cwiseMax(VectorXd::Zero(N));
    aL[0] = 0; // 左边界系数

    aR += (-F_r).cwiseMax(VectorXd::Zero(N));
    aR[N-1] = 0; // 右边界系数

    // 黎曼边界不会引入Sp
    // Sp[0] += -(max(F_l[0], 0.0)); // 左边界引入系数矩阵的不规则项
    Sp[N-1] += -(max(-F_r[0], 0.0)); // 右边界引入系数矩阵的不规则项 

    aP += aL + aR - Sp + (F_r - F_l);

    Su[N-1] += T_r*(max(-F_r[N-1], 0.0)); // 右边界用狄拉克边界条件

    return *this;
}

MatrixCoeff& MatrixCoeff::addDiffusionTerm(const Mesh* mesh, const Boundary& boundary, const Source& source)
{
    double T_l = boundary.T_left;
    double T_r = boundary.T_right;
    double T_b = boundary.T_bottom;
    double T_t = boundary.T_top;
    double q_w = boundary.q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    const VectorXd& DA_L = mesh->get_DA_L();
    const VectorXd& DA_R = mesh->get_DA_R();
    const VectorXd& DA_B = mesh->get_DA_B();
    const VectorXd& DA_T = mesh->get_DA_T();

    int N = mesh->get_N();

    aL += DA_L;
    aL[0] = 0; // 左边界系数

    aR += DA_R;
    aR[N-1] = 0; // 右边界系数

    // 黎曼边界不会引入Sp
    // Sp[0] += (-2*DA_L[0]); // 左边界引入系数矩阵的不规则项
    Sp[N-1] += (-2*DA_R[N-1]); // 右边界引入系数矩阵的不规则项 

    aP += aL + aR - Sp;

    Su[0] += -q_w*Ax; // 左边界使用黎曼边界条件
    Su[N-1] += T_r*(2*DA_R[N-1]); // 右边界用狄拉克边界条件

    return *this;
}

MatrixCoeff& MatrixCoeff::addSourceTerm(const Mesh* mesh, const Boundary& boundary, const Source& source)
{
    double S_bar = source.S_bar;

    const VectorXd& V = mesh->get_V();

    int N = mesh->get_N();

    Su += S_bar * V;

    return *this;
}