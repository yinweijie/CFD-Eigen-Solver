#ifndef __MATRIX_COEFF_H__
#define __MATRIX_COEFF_H__

#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixWrapper.h"

using Eigen::SparseMatrix;
using Eigen::BiCGSTAB;
using namespace std;

template <typename T>
class MatrixCoeff
{
private:
    const Mesh* mesh;
    // 网格数量
    int N;

    VectorXd aW, aE, aS, aN, aO, SO, SE, SW, SN, SS, Su;

    VectorXd b_m;
    VectorXd x;

    /**
     * MatrixXd和SparseMatrix的封装类，封装后的Wrapper类共同继承接口MatrixInterface，
     * 并实现接口函数MatrixInterface::setNum，这个函数用来往矩阵中插入元素
     */
    DenseMatrixWrapper dense_matrix_wrapper;
    SparseMatrixWrapper sparse_matrix_wrapper;

    double m_res;
    double epsilon;

    friend T;
public:
    MatrixCoeff(const Mesh* mesh) 
        : mesh(mesh), N(mesh->get_N())
    {
        aW = VectorXd::Zero(N);
        aE = VectorXd::Zero(N);
        aS = VectorXd::Zero(N);
        aN = VectorXd::Zero(N);
        aO = VectorXd::Zero(N);

        SO = VectorXd::Zero(N);
        SE = VectorXd::Zero(N);
        SW = VectorXd::Zero(N);
        SN = VectorXd::Zero(N);
        SS = VectorXd::Zero(N);

        Su = VectorXd::Zero(N);

        b_m = VectorXd::Zero(N);
        x = VectorXd::Zero(N);

        m_res = 0.0;
        epsilon = 1.e-10;
    }

    VectorXd& get_b_m() { return b_m; }
    VectorXd& get_x() { return x; }
    VectorXd& get_aO() { return aO; }

    // MatrixXd系数初始化
    void initDenseMatrix();

    // SparseMatrix系数初始化
    void initSparseMatrix();

    void init(MatrixInterface* matrix);

    // 系数矩阵存在非稀疏矩阵MatrixXd中，方便打印输出
    void DebugSolve(VectorXd& field_var);

    // 系数矩阵存在稀疏矩阵SparseMatrix中，用于迭代求解
    void Solve(VectorXd& field_var, double& res, double tolerance = 1.e-10);
};

template <typename T>
void MatrixCoeff<T>::initDenseMatrix()
{
    dense_matrix_wrapper = DenseMatrixWrapper(N, N);

    init(&dense_matrix_wrapper);

    b_m = Su;
}

template <typename T>
void MatrixCoeff<T>::initSparseMatrix()
{
    sparse_matrix_wrapper = SparseMatrixWrapper(N, N);

    SparseMatrix<double>& A_m = sparse_matrix_wrapper.getMatrix();

    // 每列预留5个元素的空间，用于插入
    // ref. http://eigen.tuxfamily.org/dox/group__TutorialSparse.html - Filling a sparse matrix
    A_m.reserve(VectorXi::Constant(N, 5));

    init(&sparse_matrix_wrapper);

    A_m.makeCompressed(); // optional

    b_m = Su;
}

template <typename T>
void MatrixCoeff<T>::init(MatrixInterface* matrix)
{
    for(int i = 0; i < N; i++)
    {
        int i_l = mesh->left_of(i);
        int i_r = mesh->right_of(i);
        int i_t = mesh->top_of(i);
        int i_b = mesh->bottom_of(i);

        matrix->setNum(i, i, aO[i]);

        if(!mesh->is_at_left_boundary(i))
        {
            matrix->setNum(i, i_l, -(aW[i] - SW[i]));
        }
        if(!mesh->is_at_right_boundary(i))
        {
            matrix->setNum(i, i_r, -(aE[i] - SE[i]));
        }
        if(!mesh->is_at_bottom_boundary(i))
        {
            matrix->setNum(i, i_b, -(aS[i] - SS[i]));
        }
        if(!mesh->is_at_top_boundary(i))
        {
            matrix->setNum(i, i_t, -(aN[i] - SN[i]));
        }
    }
}

template <typename T>
void MatrixCoeff<T>::DebugSolve(VectorXd& field_var)
{
    initDenseMatrix();

    MatrixXd& A_m = dense_matrix_wrapper.getMatrix();

    // 输出结果
    cout << "A_m: " << endl;
    // for(int i = 0; i < A_m.rows(); i++)
    // {
    //     for(int j = 0; j < A_m.cols(); j++)
    //     {
    //         cout << A_m(i, j) << ", ";
    //     }
    //     cout << endl;
    // }
    cout << A_m << endl;
    cout << endl;

    // 求解矩阵
    field_var = A_m.fullPivLu().solve(b_m);

    cout << "b_m: " << endl << b_m << endl;
    cout << endl;

    cout << "Solution: " << endl << field_var << endl;
}

template <typename T>
void MatrixCoeff<T>::Solve(VectorXd& field_var, double& res, double tolerance)
{
    initSparseMatrix();

    SparseMatrix<double>& A_m = sparse_matrix_wrapper.getMatrix();
    VectorXd& x = field_var;

    // 计算残差
    m_res = (b_m - A_m * x).norm();
    res = m_res;

    if(res < epsilon) return;

    // ref. http://eigen.tuxfamily.org/dox/classEigen_1_1BiCGSTAB.html
    // ref. http://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html#TutorialSparseSolverConcept
    // ref. http://eigen.tuxfamily.org/dox/group__MatrixfreeSolverExample.html

    // BiCGSTAB<SparseMatrix<double>, Eigen::IdentityPreconditioner> solver;
    BiCGSTAB<SparseMatrix<double>, Eigen::IncompleteLUT<double>> solver;
    solver.compute(A_m).setTolerance(tolerance);
    x = solver.solve(b_m);

    std::cout << "# inner iterations:     " << solver.iterations() << std::endl;
    std::cout << "estimated error: " << solver.error()      << std::endl;

    // std::cout << "Solution: " << std::endl << x << std::endl;
}

#endif