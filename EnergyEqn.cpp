#include "EnergyEqn.h"

void EnergyEqn::init_S()
{
    const VectorXd& V = mesh->get_V();

    S = S_bar * V;
}