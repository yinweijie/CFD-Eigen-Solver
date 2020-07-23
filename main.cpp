#include <iostream>
#include <eigen3/Eigen/Dense>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

namespace Inputs
{
    // # Thermal Conductivity of the bar (W/mK)
    double k = 100;
    
    // # Cross-sectional Area of the bar (m2)
    double A = 0.1;
    
    // # Length of the bar (m)
    double L = 5;
    
    // # Number of cells in the mesh
    int N = 5;
    
    // # Temperature at the left hand side of the bar (deg C)
    double T_A = 100;
    
    // # Temperature at the left hand side of the bar (deg C)
    double T_B = 200;
    
    // # Heat source per unit volume (W/m3)
    double S_bar = 1000;
}

namespace Mesh
{
    using Inputs::N;

    // 网格x方向面坐标
    VectorXd xFace(N + 1);

    // 网格x方向中心坐标
    VectorXd xCentroid(N);

    // d_LP, d_PR：网格中心与左右相邻网格中心举例
    VectorXd d_LP(N), d_PR(N);

    // k*A/d
    VectorXd DA_L(N), DA_R(N);

    // 网格体积
    VectorXd V(N);
}

namespace MatrixCoeff
{
    using Inputs::N;

    VectorXd aL(N), aR(N), aP(N), Sp(N), Su(N);

    MatrixXd A_m(N, N);
    VectorXd b_m(N);
    VectorXd x(N);
}

// 初始化网格
void initMesh(double L, int N);

// Matrix系数初始化
void initMatrix();
 
int main()
{
    // 创建网格
    initMesh(Inputs::L, Inputs::N);

    // 初始化矩阵
    initMatrix();

    // 求解矩阵
    MatrixCoeff::x = MatrixCoeff::A_m.fullPivLu().solve(MatrixCoeff::b_m);

    // 输出结果
    cout << "Solution: " << endl << MatrixCoeff::x << endl;
}

void initMesh(double L, int N)
{
    using namespace Inputs;
    using namespace Mesh;

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

// a_{p} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
void initMatrix()
{
    using namespace Inputs;
    using namespace Mesh;
    using namespace MatrixCoeff;

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