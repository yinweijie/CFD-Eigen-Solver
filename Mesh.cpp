#include "Mesh.h"

void Mesh::initMesh(const Inputs* inputs)
{
    double k = inputs->physcial_properties.k;
    double rho = inputs->physcial_properties.rho;
    double cp = inputs->physcial_properties.cp;
    double U = inputs->boundary.U;

    // x方向网格长度
    double dx = inputs->geometry.XLen / Nx;
    double dy = inputs->geometry.YLen / Ny;
    double dz = inputs->geometry.ZLen / Nz;

    // 网格横截面积
    Ax = dy * dz;
    Ay = dx * dz;
    Az = dx * dy;

    // 面坐标，x，y，z方向
    for(int i = 0; i <= Nx; i++)
    {
        xFace[i] = dx * i;
    }
    for(int i = 0; i <= Ny; i++)
    {
        yFace[i] = dy * i;
    }
    for(int i = 0; i <= Nz; i++)
    {
        zFace[i] = dz * i;
    }
    // cout << xFace << endl;

    // 网格中心坐标
    for(int i = 0; i < N; i++)
    {
        int ix = i % Nx;
        int iy = i / Nx; // floor division
        int iz = i / (Nx * Ny); // floor division

        xCentroid[i] = 0.5 * (xFace[ix] + xFace[ix+1]);
        yCentroid[i] = 0.5 * (yFace[iy] + yFace[iy+1]);
        zCentroid[i] = 0.5 * (zFace[iz] + zFace[iz+1]);
    }
    // std::cout << "xCentroid: " << xCentroid << std::endl;
    // std::cout << "yCentroid: " << yCentroid << std::endl;
    // std::cout << "zCentroid: " << zCentroid << std::endl;

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

        DA_L[i] = k * Ax / d_LP[i];
        DA_R[i] = k * Ax / d_PR[i];

        // 这里速度是均匀的
        U_l.setConstant(U);
        U_r.setConstant(U);
        F_l = rho * cp * U_l * Ax;
        F_r = rho * cp * U_r * Ax;

        // 网格体积 = faceArea * dx
        V[i] = Ax * (xFace[i+1] - xFace[i]);
    }
}