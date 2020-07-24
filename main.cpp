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


    // 创建网格
    Mesh* mesh = new Mesh(Inputs::L, Inputs::N);

    // 初始化矩阵
    MatrixCoeff* MCoeff = new MatrixCoeff(mesh);

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
}
