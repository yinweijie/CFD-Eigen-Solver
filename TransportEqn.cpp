#include "TransportEqn.h"

void TransportEqn::init_DA()
{
    const VectorXd& d_LP = mesh->get_d_LP();
    const VectorXd& d_PR = mesh->get_d_PR();
    const VectorXd& d_PT = mesh->get_d_PT();
    const VectorXd& d_BP = mesh->get_d_BP();

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();

    DA_L = gamma() * Ax * d_LP.cwiseInverse();
    DA_R = gamma() * Ax * d_PR.cwiseInverse();
    DA_T = gamma() * Ay * d_PT.cwiseInverse();
    DA_B = gamma() * Ay * d_BP.cwiseInverse();
}

void TransportEqn::init_F()
{
    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();

    const VectorXd& u_e = field->u_e;
    const VectorXd& u_w = field->u_w;
    const VectorXd& v_n = field->v_n;
    const VectorXd& v_s = field->v_s;

    F_l = density() * u_w * Ax;
    F_r = density() * u_e * Ax;
    F_b = density() * v_s * Ay;
    F_t = density() * v_n * Ay;
}
