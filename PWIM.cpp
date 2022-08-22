#include "PWIM.h"

void PWIM::updateFaceVel()
{
	for(int i = 0; i < field->cellNum; i++)
    {
        double uO = field->u[i];

        double dxdy = mesh->get_Az();
        double dx = mesh->get_dx();

        VectorXd& aO = xMatrixCoeff->get_aO();
        double AOO = aO[i];

        double pO = field->p[i];

        if(mesh->is_at_left_boundary(i))
        {
            double AOE = aO[mesh->right_of(i)];
            double pE = field->p[mesh->right_of(i)];
            double pEE = field->p[mesh->right_of(mesh->right_of(i))];
            double uE = field->u[mesh->right_of(i)];

            double gradX_pO = ((pE + pO) * 0.5 - pO) / dx;
            double gradX_pE = (pEE - pO) / (2 * dx);
            double gradX_pe = (pE - pO) / dx;

            field->u_e[i] = 0.5 * (uO + uE) + 0.5 * dxdy *
                    (gradX_pO / AOO + gradX_pE / AOE - (1 / AOE + 1 / AOO) * gradX_pe);
        }
        else if(mesh->is_at_right_boundary(i))
        {
            field->u_e[i] = inputs->boundary.U_right;
        }
        else if(mesh->is_at_left_boundary(mesh->right_of(i)))
        {

        }
        else
        {

        }
    }
}