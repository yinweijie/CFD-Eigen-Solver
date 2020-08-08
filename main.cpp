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
    // implement 2D solver

    // 读取数据
    Inputs* inputs = new Inputs("Inputs.dat");
    inputs->initInputs();

    // 创建网格
    Mesh* mesh = new Mesh(inputs);

    // 获取边界条件与源项
    Boundary& boundary = inputs->boundary;
    Source& source = inputs->source;
    // 将对流项、扩散项、源项，初始化到系数矩阵中
    MatrixCoeff* MCoeff = new MatrixCoeff(mesh, boundary, source);
    (*MCoeff).addConvectionTerm(mesh, boundary, source)
             .addDiffusionTerm(mesh, boundary, source)
             .addSourceTerm(mesh, boundary, source)
             .initMatrix(mesh, boundary, source);

    // 获取矩阵
    MatrixXd& A_m = MCoeff->get_A_m();
    VectorXd& b_m = MCoeff->get_b_m();
    VectorXd& x = MCoeff->get_x();
    // 求解矩阵
    x = A_m.fullPivLu().solve(b_m);

    // 输出结果
    cout << "Solution: " << endl << x << endl;

    delete MCoeff;
    delete mesh;
    delete inputs;
}
