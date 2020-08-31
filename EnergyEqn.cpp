#include "EnergyEqn.h"
#include "MatrixCoeff.h"

void EnergyEqn::init_S()
{
    const VectorXd& V = mesh->get_V();

    S = S_bar * V;
}

TransportEqn& EnergyEqn::addConvectionTerm()
{
    double T_l = boundary->T_left;
    double T_r = boundary->T_right;
    double T_b = boundary->T_bottom;
    double T_t = boundary->T_top;

    double q_w = boundary->q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    mat->aW += F_w.cwiseMax(VectorXd::Zero(N));
    mat->aE += (-F_e).cwiseMax(VectorXd::Zero(N));
    mat->aS += F_s.cwiseMax(VectorXd::Zero(N));
    mat->aN += (-F_n).cwiseMax(VectorXd::Zero(N));

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            mat->aW[i] = 0; // 左边界
            mat->SO[i] += -(max(F_w[i], 0.0));
            mat->Su[i] += T_l * max(F_e[i], 0.0);
        }
        if(mesh->is_at_right_boundary(i))
        {
            mat->aE[i] = 0; // 右边界
            mat->SO[i] += -(max(-F_e[i], 0.0));
            mat->Su[i] += T_r * max(-F_e[i], 0.0);
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            mat->aS[i] = 0; // 下边界
            mat->SO[i] += -(max(F_s[i], 0.0));
            mat->Su[i] += T_b * max(F_s[i], 0.0);
        }
        if(mesh->is_at_top_boundary(i))
        {
            mat->aN[i] = 0; // 上边界
            mat->SO[i] += -(max(-F_n[i], 0.0));
            mat->Su[i] += T_t * max(-F_n[i], 0.0);
        }
    }

    mat->aO += mat->aW + mat->aE + mat->aS + mat->aN - mat->SO + (F_e - F_w + F_n - F_s);

    return *this;
}

TransportEqn& EnergyEqn::addDiffusionTerm()
{
    double T_l = boundary->T_left;
    double T_r = boundary->T_right;
    double T_b = boundary->T_bottom;
    double T_t = boundary->T_top;
    double q_w = boundary->q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    mat->aW += DA_w;
    mat->aE += DA_e;
    mat->aS += DA_s;
    mat->aN += DA_n;

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            mat->aW[i] = 0; // 左边界
            mat->SO[i] += -2*DA_w[i];
            mat->Su[i] += T_l * 2*DA_w[i];
            // Su[i] += -q_w*Ax; // 左边界使用黎曼边界条件
        }
        if(mesh->is_at_right_boundary(i))
        {
            mat->aE[i] = 0; // 右边界
            mat->SO[i] += -2*DA_e[i];
            mat->Su[i] += T_r * 2*DA_e[i];
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            mat->aS[i] = 0; // 下边界
            mat->SO[i] += -2*DA_s[i];
            mat->Su[i] += T_b * 2*DA_s[i];
        }
        if(mesh->is_at_top_boundary(i))
        {
            mat->aN[i] = 0; // 上边界
            mat->SO[i] += -2*DA_n[i];
            mat->Su[i] += T_t * 2*DA_n[i];
        }
    }

    mat->aO += mat->aW + mat->aE + mat->aS + mat->aN - mat->SO;

    return *this;
}

TransportEqn& EnergyEqn::addSourceTerm()
{
    mat->Su += S;

    return *this;
}