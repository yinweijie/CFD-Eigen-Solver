#include "Mesh.h"

void Mesh::initMesh(const Inputs* inputs)
{
    // using namespace Inputs;

    // x方向网格长度
    double dx = inputs->L / N;

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

        DA_L[i] = inputs->k * inputs->A / d_LP[i];
        DA_R[i] = inputs->k * inputs->A / d_PR[i];

        // 这里速度是均匀的
        U_l.setConstant(inputs->U);
        U_r.setConstant(inputs->U);
        F_l = inputs->rho * inputs->cp * U_l * inputs->A;
        F_r = inputs->rho * inputs->cp * U_r * inputs->A;

        // 网格体积 = faceArea * dx
        V[i] = inputs->A * (xFace[i+1] - xFace[i]);
    }
}