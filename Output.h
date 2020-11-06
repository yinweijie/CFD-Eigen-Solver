#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <fstream>
#include <iostream>
#include <string>
#include "Field.h"
#include "Mesh.h"

using namespace std;

class Output
{
private:
    Mesh* mesh;
public:
    Output(Mesh* mesh) : mesh(mesh){ }

    void write(const VectorXd& var, double bc_left, double bc_right, double bc_top, double bc_bottom, string varName)
    {
        string FileName = varName + ".csv"s;

        ofstream tempFile(FileName);

        tempFile << "x, " << "y, " << "z, " << varName << endl;

        int N = mesh->get_N();

        const VectorXd& x = mesh->get_xCentroid();
        const VectorXd& y = mesh->get_yCentroid();
        const VectorXd& z = mesh->get_zCentroid();

        const VectorXd& xFace = mesh->get_xFace();
        const VectorXd& yFace = mesh->get_yFace();
        const VectorXd& zFace = mesh->get_zFace();

        // 底部边界温度
        for(int i = 0; i < xFace.size(); i++)
        {
            if(i == 0) // 左下角
            {
                tempFile << xFace[i] << ", " << 0.0 << ", " << zFace[0] << ", " << (0.5*((bc_bottom) + (bc_left))) << endl;
            }
            else if(i == xFace.size() - 1) // 右下角
            {
                tempFile << xFace[i] << ", " << 0.0 << ", " << zFace[0] << ", " << (0.5*((bc_bottom) + (bc_right))) << endl;
            }
            else
            {
                tempFile << xFace[i] << ", " << 0.0 << ", " << zFace[0] << ", " << (bc_bottom) << endl;
            }
        }

        // 顶部边界温度
        for(int i = 0; i < xFace.size(); i++)
        {
            if(i == 0) // 左上角
            {
                tempFile << xFace[i] << ", " << yFace[yFace.size()-1] << ", " << zFace[0] << ", " << (0.5*((bc_top) + (bc_left))) << endl;
            }
            else if(i == xFace.size() - 1) // 右上角
            {
                tempFile << xFace[i] << ", " << yFace[yFace.size()-1] << ", " << zFace[0] << ", " << (0.5*((bc_top) + (bc_right))) << endl;
            }
            else
            {
                tempFile << xFace[i] << ", " << yFace[yFace.size()-1] << ", " << zFace[0] << ", " << (bc_top) << endl;
            }
        }

        // 左侧边界温度 (不包括顶点)
        for(int i = 1; i < yFace.size() - 1; i++)
        {
            tempFile << 0.0 << ", " << yFace[i] << ", " << zFace[0] << ", " << (bc_left) << endl;
        }

        // 右侧边界温度 (不包括顶点)
        for(int i = 1; i < yFace.size() - 1; i++)
        {
            tempFile << xFace[xFace.size()-1] << ", " << yFace[i] << ", " << zFace[0] << ", " << (bc_right) << endl;
        }

        // 内部顶点温度
        for(int i = 0; i < N; i++)
        {
            // 体心与左下角顶点一一对应
            if(!(mesh->is_at_left_boundary(i) || mesh->is_at_bottom_boundary(i)))
            {
                double cellLeftVar = var[mesh->left_of(i)];
                double cellBottomVar = var[mesh->bottom_of(i)];
                double cellBottomLeftVar = var[mesh->left_of(mesh->bottom_of(i))];

                double varNode = 0.25 * (var[i] + cellLeftVar + cellBottomVar + cellBottomLeftVar);

                // ix, iy, iz编号正好与左下角xFace, yFace, zFace编号相同
                tempFile << xFace[mesh->ix_of(i)] << ", " << yFace[mesh->iy_of(i)] << ", " << zFace[mesh->iz_of(i)] << ", " << varNode << endl;
            }
        }
    }
};

#endif