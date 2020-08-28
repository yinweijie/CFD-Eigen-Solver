#include "MatrixCoeff.h"
#include "MatrixWrapper.h"

// a_p T_p = a_L T_L + a_R T_R + ... + S_{u}
void MatrixCoeff::initDenseMatrix()
{
    init(&dense_matrix_wrapper);

    b_m = Su;
}

void MatrixCoeff::initSparseMatrix()
{
    SparseMatrix<double> A_m = sparse_matrix_wrapper.getMatrix();

    // 每列预留5个元素的空间，用于插入
    // ref. http://eigen.tuxfamily.org/dox/group__TutorialSparse.html - Filling a sparse matrix
    A_m.reserve(VectorXi::Constant(N, 5));

    init(&sparse_matrix_wrapper);

    A_m.makeCompressed(); // optional

    b_m = Su;
}

void MatrixCoeff::init(MatrixInterface* matrix)
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
            matrix->setNum(i, i_l, -aW[i]);
        }
        if(!mesh->is_at_right_boundary(i))
        {
            matrix->setNum(i, i_r, -aE[i]);
        }
        if(!mesh->is_at_bottom_boundary(i))
        {
            matrix->setNum(i, i_b, -aS[i]);
        }
        if(!mesh->is_at_top_boundary(i))
        {
            matrix->setNum(i, i_t, -aN[i]);
        }
    }
}

MatrixCoeff& MatrixCoeff::addConvectionTerm()
{
    double T_l = boundary->T_left;
    double T_r = boundary->T_right;
    double T_b = boundary->T_bottom;
    double T_t = boundary->T_top;

    double q_w = boundary->q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    const VectorXd& F_w = eqn->get_F_w();
    const VectorXd& F_e = eqn->get_F_e();
    const VectorXd& F_s = eqn->get_F_s();
    const VectorXd& F_n = eqn->get_F_n();

    aW += F_w.cwiseMax(VectorXd::Zero(N));
    aE += (-F_e).cwiseMax(VectorXd::Zero(N));
    aS += F_s.cwiseMax(VectorXd::Zero(N));
    aN += (-F_n).cwiseMax(VectorXd::Zero(N));

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            aW[i] = 0; // 左边界
            SO[i] += -(max(F_w[i], 0.0));
            Su[i] += T_l * max(F_e[i], 0.0);
        }
        if(mesh->is_at_right_boundary(i))
        {
            aE[i] = 0; // 右边界
            SO[i] += -(max(-F_e[i], 0.0));
            Su[i] += T_r * max(-F_e[i], 0.0);
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            aS[i] = 0; // 下边界
            SO[i] += -(max(F_s[i], 0.0));
            Su[i] += T_b * max(F_s[i], 0.0);
        }
        if(mesh->is_at_top_boundary(i))
        {
            aN[i] = 0; // 上边界
            SO[i] += -(max(-F_n[i], 0.0));
            Su[i] += T_t * max(-F_n[i], 0.0);
        }
    }

    aO += aW + aE + aS + aN - SO + (F_e - F_w + F_n - F_s);

    return *this;
}

MatrixCoeff& MatrixCoeff::addDiffusionTerm()
{
    double T_l = boundary->T_left;
    double T_r = boundary->T_right;
    double T_b = boundary->T_bottom;
    double T_t = boundary->T_top;
    double q_w = boundary->q_w;

    double Ax = mesh->get_Ax();
    double Ay = mesh->get_Ay();
    double Az = mesh->get_Az();

    const VectorXd& DA_w = eqn->get_DA_w();
    const VectorXd& DA_e = eqn->get_DA_e();
    const VectorXd& DA_s = eqn->get_DA_s();
    const VectorXd& DA_n = eqn->get_DA_n();

    aW += DA_w;
    aE += DA_e;
    aS += DA_s;
    aN += DA_n;

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            aW[i] = 0; // 左边界
            SO[i] += -2*DA_w[i];
            Su[i] += T_l * 2*DA_w[i];
            // Su[i] += -q_w*Ax; // 左边界使用黎曼边界条件
        }
        if(mesh->is_at_right_boundary(i))
        {
            aE[i] = 0; // 右边界
            SO[i] += -2*DA_e[i];
            Su[i] += T_r * 2*DA_e[i];
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            aS[i] = 0; // 下边界
            SO[i] += -2*DA_s[i];
            Su[i] += T_b * 2*DA_s[i];
        }
        if(mesh->is_at_top_boundary(i))
        {
            aN[i] = 0; // 上边界
            SO[i] += -2*DA_n[i];
            Su[i] += T_t * 2*DA_n[i];
        }
    }

    aO += aW + aE + aS + aN - SO;

    return *this;
}

MatrixCoeff& MatrixCoeff::addSourceTerm()
{
    Su += eqn->get_S();

    return *this;
}

void MatrixCoeff::DebugSolve()
{
    initDenseMatrix();

    MatrixXd& A_m = dense_matrix_wrapper.getMatrix();

    // 求解矩阵
    x = A_m.fullPivLu().solve(b_m);

    // 输出结果
    cout << "A_m: " << endl << A_m << endl;
    cout << endl;

    cout << "b_m: " << endl << b_m << endl;
    cout << endl;

    cout << "Solution: " << endl << x << endl;
}

void MatrixCoeff::Solve()
{
    initSparseMatrix();

    SparseMatrix<double>& A_m = sparse_matrix_wrapper.getMatrix();

    // ref. http://eigen.tuxfamily.org/dox/classEigen_1_1BiCGSTAB.html
    // ref. http://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html#TutorialSparseSolverConcept
    // ref. http://eigen.tuxfamily.org/dox/group__MatrixfreeSolverExample.html

    // BiCGSTAB<SparseMatrix<double>, Eigen::IdentityPreconditioner> solver;
    BiCGSTAB<SparseMatrix<double>, Eigen::IncompleteLUT<double>> solver;
    solver.compute(A_m);
    x = solver.solve(b_m);

    std::cout << "#iterations:     " << solver.iterations() << std::endl;
    std::cout << "estimated error: " << solver.error()      << std::endl;

    std::cout << "x: " << std::endl << x << std::endl;
}