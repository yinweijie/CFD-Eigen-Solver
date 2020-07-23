#include <iostream>
#include <eigen3/Eigen/Dense>
#include "Inputs.h"
#include "Mesh.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

namespace MatrixCoeff
{
    using Inputs::N;

    VectorXd aL(N), aR(N), aP(N), Sp(N), Su(N);

    MatrixXd A_m(N, N);
    VectorXd b_m(N);
    VectorXd x(N);
}

// Matrix系数初始化
void initMatrix(const Mesh<Inputs::N>* mesh);
 
int main()
{
    // 创建网格
    Mesh<Inputs::N>* mesh = new Mesh<Inputs::N>(Inputs::L);

    // 初始化矩阵
    initMatrix(mesh);

    // 求解矩阵
    MatrixCoeff::x = MatrixCoeff::A_m.fullPivLu().solve(MatrixCoeff::b_m);

    // 输出结果
    cout << "Solution: " << endl << MatrixCoeff::x << endl;

    delete mesh;
}

// a_{p} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
void initMatrix(const Mesh<Inputs::N>* mesh)
{
    using namespace Inputs;
    using namespace MatrixCoeff;

    const VectorXd& DA_L = mesh->get_DA_L();
    const VectorXd& DA_R = mesh->get_DA_R();
    const VectorXd& V = mesh->get_V();

    aL = DA_L;
    aL[0] = 0; // 左边界系数

    aR = DA_R;
    aR[N-1] = 0; // 右边界系数

    Sp = VectorXd::Zero(N);
    Sp[0] = -2 * DA_L[0]; // 左边界引入系数矩阵的不规则项
    Sp[N-1] = -2 * DA_R[N-1]; // 右边界引入系数矩阵的不规则项 

    aP = aL + aR - Sp;

    Su = S_bar * V;
    Su[0] = T_A*(2*DA_L[0]) + S_bar * V[0];
    Su[N-1] = T_B*(2*DA_R[N-1]) + S_bar * V[N-1];

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