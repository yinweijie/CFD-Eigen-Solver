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
void initMatrix(const Mesh* mesh, const Inputs* inputs);

public:
    MatrixCoeff(const Mesh* mesh, const Inputs* inputs)
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
        
        initMatrix(mesh, inputs);
    }

    MatrixXd& get_A_m() { return A_m; }
    VectorXd& get_b_m() { return b_m; }
    VectorXd& get_x() { return x; }
};

#endif