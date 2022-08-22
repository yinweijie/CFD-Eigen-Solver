#include "Mesh.h"

void Mesh::initMesh(const Inputs* inputs)
{
    dx = inputs->geometry.XLen / Nx;
    dy = inputs->geometry.YLen / Ny;
    dz = inputs->geometry.ZLen / Nz;

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

    // 网格中心相关量
    for(int i = 0; i < N; i++)
    {
        if(is_at_left_boundary(i)) // 左边界的d_LP需要特殊处理
        {
            d_LP[i] = 2 * (xCentroid[i] - xFace.head(1)[0]);
            flag_d_LP[i] = 1;
        }
        if(is_at_right_boundary(i)) // 右边界的d_PR需要特殊处理
        {
            d_PR[i] = 2 * (xFace.tail(1)[0] - xCentroid[i]);
            flag_d_PR[i] = 1;
        }
        if(is_at_bottom_boundary(i)) // 下边界的d_BP需要特殊处理
        {
            d_BP[i] = 2 * (yCentroid[i] - yFace.head(1)[0]);
            flag_d_BP[i] = 1;
        }
        if(is_at_top_boundary(i)) // 上边界的d_PT需要特殊处理
        {
            d_PT[i] = 2 * (yFace.tail(1)[0] - yCentroid[i]);
            flag_d_PT[i] = 1;
        }
        
        int i_l = left_of(i);
        int i_r = right_of(i);
        int i_t = top_of(i);
        int i_b = bottom_of(i);

        // 未特殊处理的网格在这里统一赋值
        if(!flag_d_LP[i]) (d_LP[i] = xCentroid[i] - xCentroid[i_l], flag_d_LP[i]);
        if(!flag_d_PR[i]) (d_PR[i] = xCentroid[i_r] - xCentroid[i], flag_d_PR[i]);
        if(!flag_d_PT[i]) (d_PT[i] = yCentroid[i_t] - yCentroid[i], flag_d_PT[i]);
        if(!flag_d_BP[i]) (d_BP[i] = yCentroid[i] - yCentroid[i_b], flag_d_BP[i]);

        // 网格体积 = faceArea * dx
        int ix = i % Nx;
        V[i] = Ax * (xFace[ix+1] - xFace[ix]);
    }
}