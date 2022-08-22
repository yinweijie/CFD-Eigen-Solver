#ifndef __FIELD_H__
#define __FIELD_H__

#include "Mesh.h"

struct Field
{
    // cell value of the velocity
    VectorXd u; // X direction
    VectorXd v; // Y direction

    // face value of the velocity
    // Todo: 
    // 这里可以做性能优化，例如 i 网格的 u_e 等于 i+1 网格的 u_w
    // 只用保留其中一个即可
    VectorXd u_e; // east face u velocity
    VectorXd u_w; // west face u velocity
    VectorXd v_n; // north face v velocity
    VectorXd v_s; // south face v velocity

    VectorXd T; // Temperature

    VectorXd p; // Pressure

    int cellNum; // number of cells

    Field(int N)
    {
        u = VectorXd::Zero(N);
        v = VectorXd::Zero(N);
        u_e = VectorXd::Zero(N);
        u_w = VectorXd::Zero(N);
        v_n = VectorXd::Zero(N);
        v_s = VectorXd::Zero(N);

        T = VectorXd::Zero(N);

        p = VectorXd::Zero(N);

        cellNum = N;
    }
};

#endif