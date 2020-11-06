#ifndef __PWIM_H__
#define __PWIM_H__

#include "Field.h"

class PWIM
{
private:
    Field* field;
public:
    PWIM(Field* field) : field(field) { }

    void updateFaceVel();
};

#endif