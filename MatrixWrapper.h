#ifndef __MATRIX_WRAPPER_H__
#define __MATRIX_WRAPPER_H__

#include <iostream>
#include <Eigen/Sparse>
#include "MatrixInterface.h"

using Eigen::MatrixXd;
using Eigen::SparseMatrix;

class DenseMatrixWrapper : public MatrixInterface
{
private:
    MatrixXd m_dense_matrix;
public:
    DenseMatrixWrapper() = default;
    DenseMatrixWrapper(int row, int col)
    {
        m_dense_matrix = MatrixXd::Zero(row, col); 
    }

    void setNum(int row, int col, double value)
    {
        m_dense_matrix(row, col) = value;
    }

    MatrixXd& getMatrix()
    {
        return m_dense_matrix;
    }

    DenseMatrixWrapper& operator=(DenseMatrixWrapper&& rhs)
    {
        if(this != &rhs)
            m_dense_matrix = std::move(rhs.m_dense_matrix);

        return *this;
    }
};

class SparseMatrixWrapper : public MatrixInterface
{
private:
    SparseMatrix<double> m_sparse_matrix;
public:
    SparseMatrixWrapper() = default;
    SparseMatrixWrapper(int row, int col) : m_sparse_matrix(row, col) { }

    void setNum(int row, int col, double value)
    {
        // ref. http://eigen.tuxfamily.org/dox/group__TutorialSparse.html - Filling a sparse matrix
        m_sparse_matrix.insert(row, col) = value; // alternative: A.coeffRef(i,j) += v_ij;
    }

    SparseMatrix<double>& getMatrix()
    {
        return m_sparse_matrix;
    }

    SparseMatrixWrapper& operator=(SparseMatrixWrapper&& rhs)
    {
        if(this != &rhs)
            m_sparse_matrix = std::move(rhs.m_sparse_matrix);

        return *this;
    }
};

#endif