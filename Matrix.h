//
// Created by Rohan Rao on 8/13/22.
//

#ifndef MINESWEEPER_MATRIX_H
#define MINESWEEPER_MATRIX_H

#include <vector>

class Matrix {

private:
    std::vector<std::vector<float>> matrix;
    int numRows;
    int numCols;

public:
    Matrix(int n_Rows, int n_Cols);
    Matrix &Transpose();
    Matrix &operator*(Matrix &rhs);
    bool operator=(Matrix &rhs);
    std::vector<float> *operator[](int row);
    void print();
    std::vector<float> *getRow(int index);
    std::vector<float> *getColumn(int index);
    int insertRow(int i_row, std::vector<float> &n_row);
    int insertColums(int i_col, std::vector<float> &n_col);
    int AugmentMatrix(Matrix &rhs);
    int rowInterchage(int row1, int row2);
    void rowScaling(int i_row, float mult);
    int rowReplacement(int i_row, int e_row, float multiple);
    int AugmentCol(vector<float> &n_Col);
    int getNumCols();
    int getNumRows();
};

#endif //MINESWEEPER_MATRIX_H
