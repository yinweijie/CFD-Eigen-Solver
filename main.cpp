#include <iostream>
#include <string>
#include <Eigen/Dense>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
#include "Field.h"
#include "EnergyEqn.h"
#include "Output.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

int main()
{
    // 读取数据
    Inputs* inputs = new Inputs("Inputs.dat");

    // 创建网格
    Mesh* mesh = new Mesh(inputs);

    // 创建标量场
    Field* field = new Field(mesh->get_N());

    //////////////////////////////// EnergyEqn /////////////////////////////////
    // 创建能量方程系数矩阵
    MatrixCoeff<EnergyEqn>* matrix_coeff = new MatrixCoeff<EnergyEqn>(mesh);

    // 获取边界条件与源项
    Boundary& boundary = inputs->boundary;
    Source& source = inputs->source;

    // 创建能量输运方程
    TransportEqn* eqn = new EnergyEqn(mesh, field, inputs, matrix_coeff, &boundary, &source);
    eqn->init();
    (*eqn).addConvectionTerm().addDiffusionTerm().addSourceTerm();

    // 求解矩阵
    // matrix_coeff->DebugSolve(&(field->T));
    matrix_coeff->Solve(&(field->T));

    // 变量输出
    Output out(mesh);
    out.write(field->T, boundary.T_left, boundary.T_right, boundary.T_top, boundary.T_bottom, "Temperature");
    //////////////////////////////// EnergyEqn /////////////////////////////////

    // delete matrix_coeff;
    // delete eqn;
    // delete field;
    // delete mesh;
    // delete inputs;
}
