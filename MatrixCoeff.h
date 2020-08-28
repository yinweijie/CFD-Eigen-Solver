#ifndef __MATRIX_COEFF_H__
#define __MATRIX_COEFF_H__

#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
#include "Inputs.h"
#include "Mesh.h"
#include "MatrixWrapper.h"
#include "Field.h"
#include "TransportEqn.h"

using Eigen::SparseMatrix;
using Eigen::BiCGSTAB;
using namespace std;

// N: 网格数
class MatrixCoeff
{
private:
    const Mesh* mesh;
    const Boundary* boundary;
    const Source* source;
    // 网格数量
    int N;

    VectorXd aW, aE, aS, aN, aO, SO, Su;

    VectorXd b_m;
    VectorXd x;

    /**
     * MatrixXd和SparseMatrix的封装类，封装后的Wrapper类共同继承接口MatrixInterface，
     * 并实现接口函数MatrixInterface::setNum，这个函数用来往矩阵中插入元素
     */
    DenseMatrixWrapper dense_matrix_wrapper;
    SparseMatrixWrapper sparse_matrix_wrapper;

    Field* field;

    TransportEqn* eqn;
public:
    MatrixCoeff(const Mesh* mesh, const Boundary* boundary, const Source* source, Field* field, TransportEqn* eqn) 
        : mesh(mesh), boundary(boundary), source(source), N(mesh->get_N()),
          dense_matrix_wrapper(N, N), sparse_matrix_wrapper(N, N), field(field), eqn(eqn)
    {
        aW = VectorXd::Zero(N);
        aE = VectorXd::Zero(N);
        aS = VectorXd::Zero(N);
        aN = VectorXd::Zero(N);
        aO = VectorXd::Zero(N);

        SO = VectorXd::Zero(N);
        Su = VectorXd::Zero(N);

        b_m = VectorXd::Zero(N);
        x = VectorXd::Zero(N);
    }

    VectorXd& get_b_m() { return b_m; }
    VectorXd& get_x() { return x; }

    // MatrixXd系数初始化
    void initDenseMatrix();

    // SparseMatrix系数初始化
    void initSparseMatrix();

    void init(MatrixInterface* matrix);

    MatrixCoeff& addConvectionTerm();
    MatrixCoeff& addDiffusionTerm();
    MatrixCoeff& addSourceTerm();

    // 系数矩阵存在非稀疏矩阵MatrixXd中，方便打印输出
    void DebugSolve();

    // 系数矩阵存在稀疏矩阵SparseMatrix中，用于迭代求解
    void Solve();
};

#endif