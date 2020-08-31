#ifndef __ENERGYEQN_H__
#define __ENERGYEQN_H__

#include "TransportEqn.h"
#include "Inputs.h"

class EnergyEqn : public TransportEqn
{
private:
    double k;
    double cp;
    double S_bar;

    MatrixCoeff<EnergyEqn>* mat;

    double gamma() override { return k; }
    double density() override { return rho * cp; }
    void init_S();
public:
    EnergyEqn(Mesh* mesh, Field* field, Inputs* inputs, MatrixCoeff<EnergyEqn>* matrix_coeff, Boundary* boundary, Source* source)
         : TransportEqn(mesh, field, inputs, boundary, source)
    {
        k = inputs->physcial_properties.k;
        cp = inputs->physcial_properties.cp;
        S_bar = inputs->source.S_bar;

        mat = matrix_coeff;

        init_S();
    }

    TransportEqn& addConvectionTerm() override;
    TransportEqn& addDiffusionTerm() override;
    TransportEqn& addSourceTerm() override;
};

#endif