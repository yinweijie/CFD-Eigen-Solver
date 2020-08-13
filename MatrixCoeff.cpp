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

        matrix->setNum(i, i, aP[i]);

        if(!mesh->is_at_left_boundary(i))
        {
            matrix->setNum(i, i_l, -aL[i]);
        }
        if(!mesh->is_at_right_boundary(i))
        {
            matrix->setNum(i, i_r, -aR[i]);
        }
        if(!mesh->is_at_bottom_boundary(i))
        {
            matrix->setNum(i, i_b, -aB[i]);
        }
        if(!mesh->is_at_top_boundary(i))
        {
            matrix->setNum(i, i_t, -aT[i]);
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

    const VectorXd& F_l = mesh->get_F_l();
    const VectorXd& F_r = mesh->get_F_r();
    const VectorXd& F_b = mesh->get_F_b();
    const VectorXd& F_t = mesh->get_F_t();

    aL += F_l.cwiseMax(VectorXd::Zero(N));
    aR += (-F_r).cwiseMax(VectorXd::Zero(N));
    aB += F_b.cwiseMax(VectorXd::Zero(N));
    aT += (-F_t).cwiseMax(VectorXd::Zero(N));

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            aL[i] = 0; // 左边界
            Sp[i] += -(max(F_l[i], 0.0));
            Su[i] += T_l * max(F_l[i], 0.0);
        }
        if(mesh->is_at_right_boundary(i))
        {
            aR[i] = 0; // 右边界
            Sp[i] += -(max(-F_r[i], 0.0));
            Su[i] += T_r * max(-F_r[i], 0.0);
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            aB[i] = 0; // 下边界
            Sp[i] += -(max(F_b[i], 0.0));
            Su[i] += T_b * max(F_b[i], 0.0);
        }
        if(mesh->is_at_top_boundary(i))
        {
            aT[i] = 0; // 上边界
            Sp[i] += -(max(-F_t[i], 0.0));
            Su[i] += T_t * max(-F_t[i], 0.0);
        }
    }

    aP += aL + aR + aB + aT - Sp + (F_r - F_l + F_t - F_b);

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

    const VectorXd& DA_L = mesh->get_DA_L();
    const VectorXd& DA_R = mesh->get_DA_R();
    const VectorXd& DA_B = mesh->get_DA_B();
    const VectorXd& DA_T = mesh->get_DA_T();

    aL += DA_L;
    aR += DA_R;
    aB += DA_B;
    aT += DA_T;

    for(int i = 0; i < N; i++)
    {
        if(mesh->is_at_left_boundary(i))
        {
            aL[i] = 0; // 左边界
            Sp[i] += -2*DA_L[i];
            Su[i] += T_l * 2*DA_L[i];
            // Su[i] += -q_w*Ax; // 左边界使用黎曼边界条件
        }
        if(mesh->is_at_right_boundary(i))
        {
            aR[i] = 0; // 右边界
            Sp[i] += -2*DA_R[i];
            Su[i] += T_r * 2*DA_R[i];
        }
        if(mesh->is_at_bottom_boundary(i))
        {
            aB[i] = 0; // 下边界
            Sp[i] += -2*DA_B[i];
            Su[i] += T_b * 2*DA_B[i];
        }
        if(mesh->is_at_top_boundary(i))
        {
            aT[i] = 0; // 上边界
            Sp[i] += -2*DA_T[i];
            Su[i] += T_t * 2*DA_T[i];
        }
    }

    aP += aL + aR + aB + aT - Sp;

    return *this;
}

MatrixCoeff& MatrixCoeff::addSourceTerm()
{
    double S_bar = source->S_bar;

    const VectorXd& V = mesh->get_V();

    int N = mesh->get_N();

    Su += S_bar * V;

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