#ifndef __MATRIX_INTERFACE__
#define __MATRIX_INTERFACE__

class MatrixInterface
{
public:
    virtual void setNum(int row, int col, double value) = 0;
    virtual ~MatrixInterface() = 0;
};

#endif