#include <iostream>
#include <eigen3/Eigen/Dense>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


 
int main()
{
    // 创建网格
    Mesh<Inputs::N>* mesh = new Mesh<Inputs::N>(Inputs::L);

    // 初始化矩阵
    MatrixCoeff<Inputs::N>* MCoeff = new MatrixCoeff<Inputs::N>(mesh);

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
