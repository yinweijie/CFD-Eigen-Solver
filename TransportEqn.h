#ifndef __TRANSPORTEQN_H__
#define __TRANSPORTEQN_H__

#include "Mesh.h"
#include "Field.h"
#include "Inputs.h"

class TransportEqn
{
protected:
    Mesh* mesh;
    int N;

    Field* field;

    Inputs* inputs;

    // Energy Eqn: DA = k * A / d
    // Momentum Eqn: DA = mu * A / d
    VectorXd DA_L, DA_R, DA_B, DA_T;

    // Energy Eqn: F = rho * cp * U * A
    // Momentum Eqn: F = rho * U * A
    VectorXd F_l, F_r, F_b, F_t;

    // Energy Eqn: S = S_bar * V
    // X Momentum Eqn: S = dp / dx
    // Y Momentum Eqn: S = dp / dy
    VectorXd S;

    double rho;

    // 注意：init_DA()和init_F()都调用了虚函数，因此不能放在构造函数里
    void init_DA();
    void init_F();
public:
    TransportEqn(Mesh* mesh, Field* field, Inputs* inputs) : mesh(mesh), N(mesh->get_N()), field(field), inputs(inputs)
    {
        DA_L = VectorXd(N);
        DA_R = VectorXd(N);
        DA_B = VectorXd(N);
        DA_T = VectorXd(N);

        F_l = VectorXd(N);
        F_r = VectorXd(N);
        F_b = VectorXd(N);
        F_t = VectorXd(N);

        S = VectorXd(N);

        rho = inputs->physcial_properties.rho;
    }

    const VectorXd& get_DA_L() const { return DA_L; }
    const VectorXd& get_DA_R() const { return DA_R; }
    const VectorXd& get_DA_B() const { return DA_B; }
    const VectorXd& get_DA_T() const { return DA_T; }

    const VectorXd& get_F_l() const { return F_l; }
    const VectorXd& get_F_r() const { return F_r; }
    const VectorXd& get_F_b() const { return F_b; }
    const VectorXd& get_F_t() const { return F_t; }

    const VectorXd& get_S() const { return S; }

    void init()
    {
        init_DA();
        init_F();
    }

    // Energy Eqn: gamma = k
    // Momentum Eqn: gamma = mu
    virtual double gamma() = 0;

    // Energy Eqn: density = rho * cp
    // Momentum Eqn: density = rho
    virtual double density() = 0;
};

#endif