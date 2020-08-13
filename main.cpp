#include <iostream>
#include <Eigen/Dense>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

int main()
{
    // 读取数据
    Inputs* inputs = new Inputs("Inputs.dat");

    // 创建网格
    Mesh* mesh = new Mesh(inputs);

    // 获取边界条件与源项
    Boundary& boundary = inputs->boundary;
    Source& source = inputs->source;
    // 将对流项、扩散项、源项，初始化到系数矩阵中
    MatrixCoeff* matrix_coeff = new MatrixCoeff(mesh, &boundary, &source);
    (*matrix_coeff).addConvectionTerm()
                   .addDiffusionTerm()
                   .addSourceTerm();

    // 求解矩阵
    // matrix_coeff->DebugSolve();
    matrix_coeff->Solve();

    delete matrix_coeff;
    delete mesh;
    delete inputs;
}
