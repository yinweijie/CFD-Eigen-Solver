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
    VectorXd DA_w, DA_e, DA_s, DA_n;

    // Energy Eqn: F = rho * cp * U * A
    // Momentum Eqn: F = rho * U * A
    VectorXd F_w, F_e, F_s, F_n;

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
        DA_w = VectorXd(N);
        DA_e = VectorXd(N);
        DA_s = VectorXd(N);
        DA_n = VectorXd(N);

        F_w = VectorXd(N);
        F_e = VectorXd(N);
        F_s = VectorXd(N);
        F_n = VectorXd(N);

        S = VectorXd(N);

        rho = inputs->physcial_properties.rho;
    }

    const VectorXd& get_DA_w() const { return DA_w; }
    const VectorXd& get_DA_e() const { return DA_e; }
    const VectorXd& get_DA_s() const { return DA_s; }
    const VectorXd& get_DA_n() const { return DA_n; }

    const VectorXd& get_F_w() const { return F_w; }
    const VectorXd& get_F_e() const { return F_e; }
    const VectorXd& get_F_s() const { return F_s; }
    const VectorXd& get_F_n() const { return F_n; }

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