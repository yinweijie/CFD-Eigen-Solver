#include <iostream>
#include <string>
#include <Eigen/Dense>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
#include "Field.h"
#include "EnergyEqn.h"
#include "XMomentumEqn.h"
#include "YMomentumEqn.h"
#include "Output.h"
#include "PWIM.h"

#define MAM_ITER 2000
 
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

    // 初始化field
    field->u.setConstant(0.0);      field->v.setConstant(0.0);
    field->p.setConstant(0.0);      field->T.setConstant(0.0);
    field->u_e.setConstant(0.0);    field->u_w.setConstant(0.0);
    field->v_n.setConstant(0.0);    field->v_s.setConstant(0.0);

    //////////////////////////////// MomentumEqn /////////////////////////////////
    // 创建动量方程系数矩阵
    MatrixCoeff<XMomentumEqn>* xMatrixCoeff = new MatrixCoeff<XMomentumEqn>(mesh);
    MatrixCoeff<YMomentumEqn>* yMatrixCoeff = new MatrixCoeff<YMomentumEqn>(mesh);

    // 获取边界条件与源项
    Boundary& boundary = inputs->boundary;
    Source& source = inputs->source;

    // 创建动量输运方程
    XMomentumEqn* xMomentumEqn = new XMomentumEqn(mesh, field, inputs, xMatrixCoeff, &boundary, &source);
    YMomentumEqn* yMomentumEqn = new YMomentumEqn(mesh, field, inputs, yMatrixCoeff, &boundary, &source);

    //=============================== Start Outer Loop Iteration ================================//

    double tol_outer = 1.e-10;
    double tol_inner = 1.e-3;
    double relax_momentum = 0.8;
    double relax_pressure = 0.2;

    double res_u = 0.0;
    double res_v = 0.0;
    double res_p = 0.0;

    PWIM pwim(inputs, field, mesh, xMatrixCoeff, yMatrixCoeff);

    // for(int iter = 0; iter < MAM_ITER; iter++)
    // {
        /* call links */ // 计算Link coefficient，并初始化矩阵系数
    
        xMomentumEqn->init(); // init_DA(), init_F()
        (*xMomentumEqn).addConvectionTerm().addDiffusionTerm().addSourceTerm();

        yMomentumEqn->init();
        (*yMomentumEqn).addConvectionTerm().addDiffusionTerm().addSourceTerm();

        /* call solve_x_mom */ // 求解矩阵

        xMatrixCoeff->Solve(field->u, res_u, tol_inner);

        /* call solve_y_mom */

        yMatrixCoeff->Solve(field->v, res_v, tol_inner);

        /* call face_velocity */ // Face Velocity using PWIM

        pwim.updateFaceVel();

        /* call solve_pp */

        /* call uv_correct */

        /* call pres_correct */

    //     if(res_u < tol_outer && res_v < tol_outer && res_p < tol_outer) break;
    // }

    //================================ End Outer Loop Iteration =================================//

    // 变量输出
    Output out(mesh);
    out.write(field->u, boundary.U_left, boundary.U_right, boundary.U_top, boundary.U_bottom, "u");
    out.write(field->v, boundary.V_left, boundary.V_right, boundary.V_top, boundary.V_bottom, "v");
    //////////////////////////////// MomentumEqn /////////////////////////////////

    //////////////////////////////// EnergyEqn /////////////////////////////////
    // // 创建能量方程系数矩阵
    // MatrixCoeff<EnergyEqn>* matrix_coeff = new MatrixCoeff<EnergyEqn>(mesh);

    // // 获取边界条件与源项
    // Boundary& boundary = inputs->boundary;
    // Source& source = inputs->source;

    // // 创建能量输运方程
    // TransportEqn* eqn = new EnergyEqn(mesh, field, inputs, matrix_coeff, &boundary, &source);
    // eqn->init();
    // (*eqn).addConvectionTerm().addDiffusionTerm().addSourceTerm();

    // // 求解矩阵
    // // matrix_coeff->DebugSolve(&(field->T));
    // matrix_coeff->Solve(&(field->T));

    // // 变量输出
    // Output out(mesh);
    // out.write(field->T, boundary.T_left, boundary.T_right, boundary.T_top, boundary.T_bottom, "Temperature");
    //////////////////////////////// EnergyEqn /////////////////////////////////

    // delete matrix_coeff;
    // delete eqn;
    // delete field;
    // delete mesh;
    // delete inputs;
}
