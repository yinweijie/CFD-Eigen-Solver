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

    double gamma() override { return k; }
    double density() override { return rho * cp; }
    void init_S();
public:
    EnergyEqn(Mesh* mesh, Field* field, Inputs* inputs) : TransportEqn(mesh, field, inputs)
    {
        k = inputs->physcial_properties.k;
        cp = inputs->physcial_properties.cp;
        S_bar = inputs->source.S_bar;

        init_S();
    }
};

#endif