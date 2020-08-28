#ifndef __MATRIX_INTERFACE_H__
#define __MATRIX_INTERFACE_H__

class MatrixInterface
{
public:
    virtual void setNum(int row, int col, double value) = 0;
    virtual ~MatrixInterface() = 0;
};

#endif