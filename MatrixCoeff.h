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
    VectorXd aL, aR, aB, aT, aP, Sp, Su;

    MatrixXd A_m;
    VectorXd b_m;
    VectorXd x;

public:
    MatrixCoeff(const Mesh* mesh, const Boundary& boundary, const Source& source)
    {
        int N = mesh->get_N();

        aL = VectorXd::Zero(N);
        aR = VectorXd::Zero(N);
        aB = VectorXd::Zero(N);
        aT = VectorXd::Zero(N);
        aP = VectorXd::Zero(N);

        Sp = VectorXd::Zero(N);
        Su = VectorXd::Zero(N);

        A_m = MatrixXd::Zero(N, N);
        b_m = VectorXd::Zero(N);
        x = VectorXd::Zero(N);
    }

    MatrixXd& get_A_m() { return A_m; }
    VectorXd& get_b_m() { return b_m; }
    VectorXd& get_x() { return x; }

    MatrixCoeff& addConvectionTerm(const Mesh* mesh, const Boundary& boundary, const Source& source);
    MatrixCoeff& addDiffusionTerm(const Mesh* mesh, const Boundary& boundary, const Source& source);
    MatrixCoeff& addSourceTerm(const Mesh* mesh, const Boundary& boundary, const Source& source);
    
    // Matrix系数初始化
    void initMatrix(const Mesh* mesh, const Boundary& boundary, const Source& source);
};

#endif