#include <iostream>
#include <Eigen/Dense>
#include <memory>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

int main()
{
    // 创建网格
    unique_ptr<Mesh> mesh = make_unique<Mesh>(Inputs::L, Inputs::N);

    // 初始化矩阵
    unique_ptr<MatrixCoeff> MCoeff = make_unique<MatrixCoeff>(mesh.get());

    // 获取矩阵
    MatrixXd& A_m = MCoeff->get_A_m();
    VectorXd& b_m = MCoeff->get_b_m();
    VectorXd& x = MCoeff->get_x();

    // 求解矩阵
    x = A_m.fullPivLu().solve(b_m);

    // 输出结果
    cout << "Solution: " << endl << x << endl;
}
