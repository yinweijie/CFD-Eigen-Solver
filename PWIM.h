#ifndef __PWIM_H__
#define __PWIM_H__

#include "Field.h"
#include "Mesh.h"
#include "MatrixCoeff.h"
#include "XMomentumEqn.h"
#include "YMomentumEqn.h"
#include "Inputs.h"

class PWIM
{
private:
    Inputs* inputs;
    Field* field;
    Mesh* mesh;
    MatrixCoeff<XMomentumEqn>* xMatrixCoeff;
    MatrixCoeff<YMomentumEqn>* yMatrixCoeff;

    using XMat = MatrixCoeff<XMomentumEqn>;
    using YMat = MatrixCoeff<YMomentumEqn>;

public:
    PWIM(Inputs* inputs_, Field* field_, Mesh* mesh_, XMat* xMat, YMat* yMat)
        : inputs(inputs_), field(field_), mesh(mesh_), xMatrixCoeff(xMat), yMatrixCoeff(yMat) { }

    void updateFaceVel();
};

#endif