#include "YMomentumEqn.h"
#include "MatrixCoeff.h"

void YMomentumEqn::init_S()
{
    double Ay = mesh->get_Ay();
    VectorXd& p = field->p;

    for(int i = 0; i < N; i++)
    {
        int i_n = mesh->top_of(i);
        int i_s = mesh->bottom_of(i);

        if(mesh->is_at_top_boundary(i))
        {
            S[i] = (p[i_s] - p[i]) * Ay / 2;
        }
        else if(mesh->is_at_bottom_boundary(i))
        {
            S[i] = (p[i] - p[i_n]) * Ay / 2;
        }
        else
        {
            S[i] = (p[i_s] -p[i_n]) * Ay / 2;
        }
    }
}

TransportEqn& YMomentumEqn::addConvectionTerm()
{
    double V_t = boundary->V_top;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    mat->aW += F_w.cwiseMax(VectorXd::Zero(N));
    mat->aE += (-F_e).cwiseMax(VectorXd::Zero(N));
    mat->aS += F_s.cwiseMax(VectorXd::Zero(N));
    mat->aN += (-F_n).cwiseMax(VectorXd::Zero(N));

    // 边界条件这里暂时先写死，后期再做通用性优化
    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            mat->aW[i] = 0.0; // 左边界
            mat->SO[i] += 0.0;
            mat->Su[i] += 0.0;
            F_w[i] = 0;
        }
        if(mesh->is_at_right_boundary(i))
        {
            mat->aE[i] = 0.0; // 右边界
            mat->SO[i] += 0.0;
            mat->Su[i] += 0.0;
            F_e[i] = 0;
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            mat->aS[i] = 0; // 下边界
            mat->SO[i] += 0.0;
            mat->Su[i] += 0.0;
            F_s[i] = 0;
        }
        if(mesh->is_at_top_boundary(i))
        {
            mat->aN[i] = 0; // 上边界
            mat->SO[i] += 0;
            mat->Su[i] += -rho * V_t * V_t;
            F_n[i] = 0;
        }
    }

    mat->aO += mat->aW + mat->aE + mat->aS + mat->aN - mat->SO + (F_e - F_w + F_n - F_s);

    return *this;
}

TransportEqn& YMomentumEqn::addDiffusionTerm()
{
    double V_t = boundary->V_top;

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
            mat->SO[i] += -3*DA_w[i];
            mat->SE[i] += -DA_w[i] / 3;
            mat->Su[i] += 0.0;
        }
        if(mesh->is_at_right_boundary(i))
        {
            mat->aE[i] = 0; // 右边界
            mat->SO[i] += -3*DA_e[i];
            mat->SW[i] += -DA_e[i] / 3;
            mat->Su[i] += 0.0;
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            mat->aS[i] = 0; // 下边界
            mat->SO[i] += -3*DA_s[i];
            mat->SN[i] += -DA_s[i] / 3;
            mat->Su[i] += 0.0;
        }
        if(mesh->is_at_top_boundary(i))
        {
            mat->aN[i] = 0; // 上边界
            mat->SO[i] += -3*DA_n[i];
            mat->SS[i] += DA_n[i] / 3;
            mat->Su[i] += V_t * (8.0/3)*DA_n[i];
        }
    }

    mat->aO += mat->aW + mat->aE + mat->aS + mat->aN - mat->SO;

    return *this;
}

TransportEqn& YMomentumEqn::addSourceTerm()
{
    mat->Su += S; // 将S^u加到S_u一起

    return *this;
}