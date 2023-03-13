//
// Created by Rohan Rao on 8/13/22.
//

#include <iostream>
#include "Matrix.h"
#include <SFML/Graphics.hpp>


Matrix::Matrix(int n_rows, int n_cols){
    this->numCols = n_cols;
    this->numRows = n_rows;

    for(int i = 0; i < n_rows; i++){
        vector<float> omar;
        for(int j = 0; j < n_cols; j++){
            omar.push_back(0);
        }
        matrix.push_back(omar);
    }
}

int Matrix::getNumCols(){
    return this->numCols;
}

int Matrix::getNumRows() {
    return this->numRows;
}

vector<float>* Matrix::operator[](int row){
    return &(this->matrix[row]);
}

vector<float>* Matrix::getRow(int index){
    return &(this->matrix[index]);

}

std::vector<float>* Matrix::getColumn(int index){
    vector<float>* colVector = new vector<float>;
    for(int i = 0; i < numRows; i++){
        colVector->push_back(matrix[i][index]);
    }
    return colVector;
}

//Returns a 1 if the row insertion was successful -1 if it wasnt successsful
int Matrix::insertRow(int i_row, std::vector<float> &n_row) {
    if(i_row < 0 || i_row > this->numRows - 1){
        cout<<"Row vector replacement failed! 1 "<<endl;
        return -1;
    }
    else{
        if(n_row.size() == this->numCols){
            std::vector<float>* ogVector = &this->matrix[i_row];
            for(int i = 0; i < this->numCols; i++){
                ogVector->at(i) = n_row.at(i);
            }
            return 1;
        }
        else{
            cout<<numCols<<endl;
            cout<<n_row.size()<<endl;

            cout<<"Row vector replacement failed! 2 "<<endl;
            return -1;
        }

    }
}

int Matrix::insertColums(int i_col, std::vector<float> &n_col) {
    if(i_col < 0 ||  i_col > this->numCols - 1){
        cout<<"Column vector replacement failed 1"<<endl;
        return -1;
    }
    else{
        if(n_col.size() == this->numRows){
            std::vector<float>* ogVector = this->getColumn(i_col);
            for(int i = 0; i < this->numRows; i++){
                ogVector->at(i) = n_col.at(i);
            }
            return 1;
        }
        else{
            cout<<"Column vector replacement failed 2"<<endl;
            return -1;
        }
    }
}

//Returns a new matrix representing this->matrix * rhs
Matrix &Matrix::operator*(Matrix& rhs) {
    Matrix *king = nullptr;
    if(this->numRows == rhs.getNumCols()){
        int numRows = this->numCols;
        int numCols = rhs.getNumRows();
        king = new Matrix(numRows, numCols);

        for(int i = 0; i < numRows; i++){
            float rowColSum = 0;
            for(int j = 0; j < numCols; j++) {
                int currRow = i;
                int currCol = j;

                vector<float>* lhsRow = this->getRow(currRow);
                vector<float>* rhsCol = rhs.getColumn(currCol);


                for(int i = 0 ; i < this->numRows; i++){
                    rowColSum += lhsRow->at(i) * (rhsCol->at(i));
                }

                king->getRow(i)->at(j) = rowColSum;
            }
        }
        return *king;
    }
    else{
        cout<<"Matrix multiplication failed!"<<endl;
        return *king;
    }
}

//Add a column vector to the Matrix returns 1 if it was successful returns 0 if it was a failure
int Matrix::AugmentCol(vector<float>& n_Col) {
    if(n_Col.size() == this->numRows) {
        this->numCols++;
        for(int i = 0; i < this->numRows; i++){
            this->matrix.at(i).push_back(n_Col.at(i));
        }
        return 1;
    }
    else{
        cout<<"Failure to Augment column"<<endl;
        return -1;

    }
}

int Matrix::rowInterchage(int i_row, int e_row){
    if((0 < i_row < this->numRows) && (0 < e_row < this->numRows)) {
        vector<float> i_rowVec = this->matrix[i_row];
        vector<float> e_rowVec = this->matrix[e_row];

        this->insertRow(i_row, e_rowVec);
        this->insertRow(e_row, i_rowVec);
        return 1;
    }
    else{
        cout<<"row interchange failed!"<<endl;
        return -1;
    }
}

int Matrix::rowReplacement(int i_row, int e_row, float multiple) {
    if((0 < i_row < this->numRows) && (0 < e_row < this->numRows)) {
        vector<float> modVector;

        vector<float>* rowToReplace = this->getRow(e_row);
        vector<float>* inspVector = this->getRow(i_row);

        for(int i = 0; i < inspVector->size(); i++){
            float val = rowToReplace->at(i) + (multiple * inspVector->at(i));
            modVector.push_back(val);
        }

        this->insertRow(e_row, modVector);
    }
    else{
        cout<<"Row replacement failed!"<<endl;
        return -1;
    }

}

void Matrix::rowScaling(int i_row, float mult){
    for(int i  = 0; i < this->getRow(i_row)->size(); i++){
        this->getRow(i_row)->at(i) *= mult;
    }
}





static vector<float>* rref(Matrix& A, vector<float> &B) {

    if (A.AugmentCol(B) == 1) {
        //Gets the pivot point in form (row, col)
        sf::Vector2i pivotPoint(0, 0);
        int pivotRow = pivotPoint.x;
        int pivotColumn = pivotPoint.y;
        float pivotValue = 0;

        //Traverse the rows and check if the value of
        // the row in the pivot column
        for (int j = 0; j < A.getNumRows(); j++) {
            pivotValue = A[pivotPoint.x]->at(pivotPoint.y);

            for (int i = pivotPoint.x + 1; i < A.getNumRows(); i++) {
                if (A.getRow(i)->at(pivotPoint.y) != 0) {
                    float currVal = A.getRow(i)->at(pivotPoint.x);
                    A.rowReplacement(pivotPoint.x, i, -(currVal / pivotValue));
                }
            }
            pivotPoint.x++;
            pivotPoint.y++;
        }





        //Reversing the gaussian Elimination to get in RREF
        for(int k = A.getNumRows() - 1; k > 0; k--){
            pivotValue = A[k]->at(k);
            for(int i = k - 1; i >= 0; i--){
                if (A.getRow(i)->at(k) != 0) {
                    float currVal = A.getRow(i)->at(k);
                    A.rowReplacement(k, i, -(currVal / pivotValue));
                }
            }
        }


        for(int i = 0; i < A.getNumRows(); i++){
            A.rowScaling(i, 1/(A[i]->at(i)));
        }


        vector<float> *copy = new vector<float>;
        for(int i = 0; i < A.getColumn(A.getNumCols() - 1)->size(); i++){
            copy->push_back((A.getColumn(A.getNumCols() - 1)->at(i))/(A[i]->at(i)));
        }
        return copy;
    }
}


static vector<float>* rref(Matrix& A) {
        //Gets the pivot point in form (row, col)
        sf::Vector2i pivotPoint(0, 0);
        int pivotRow = pivotPoint.x;
        int pivotColumn = pivotPoint.y;
        float pivotValue = 0;

        //Traverse the rows and check if the value of
        // the row in the pivot column
        for (int j = 0; j < A.getNumRows(); j++) {
            pivotValue = A[pivotPoint.x]->at(pivotPoint.y);

            for (int i = pivotPoint.x + 1; i < A.getNumRows(); i++) {
                if (A.getRow(i)->at(pivotPoint.y) != 0) {
                    float currVal = A.getRow(i)->at(pivotPoint.x);
                    A.rowReplacement(pivotPoint.x, i, -(currVal / pivotValue));
                }
            }
            pivotPoint.x++;
            pivotPoint.y++;
        }

        //Reversing the gaussian Elimination to get in RREF
        for(int k = A.getNumRows() - 1; k > 0; k--){
            pivotValue = A[k]->at(k);
            for(int i = k - 1; i >= 0; i--){
                if (A.getRow(i)->at(k) != 0) {
                    float currVal = A.getRow(i)->at(k);
                    A.rowReplacement(k, i, -(currVal / pivotValue));
                }
            }
        }


        for(int i = 0; i < A.getNumRows(); i++){
            A.rowScaling(i, 1/(A[i]->at(i)));
        }


        vector<float> *copy = new vector<float>;
        for(int i = 0; i < A.getColumn(A.getNumCols() - 1)->size(); i++){
            copy->push_back((A.getColumn(A.getNumCols() - 1)->at(i))/(A[i]->at(i)));
        }
        return copy;
    }


    static std::vector<float>* genIntegrateWithError(float d, float lBound, float uBound, float A, int count, bool E){
        std::vector<float>* tileMultVec = new std::vector<float>;
        if(count == 0 || (pow(uBound, d+1) - pow(lBound, d+1) == 0)){
            cout<<"Bitch ass"<<endl;
            return nullptr;
        }
        else {
            float m = ((d + 1) * A) / (pow(uBound, d + 1) - pow(lBound, d + 1));
            float error = 0;

            float funcSum = 0;
            for (int i = 1; i < count; i++) {
                funcSum += m * pow(i, d);
            }

            error = (A - funcSum) / (float)count;

        for(int i = 1; i < count; i++){
            float currTerm = m * pow(i, d) + error;
            tileMultVec->push_back(currTerm);
            }
        }
        return tileMultVec;
    }


Matrix& Matrix::Transpose() {
    Matrix *tMatrix = new Matrix(this->numCols, this->numRows);
    for (int i = 0; i < tMatrix->numRows; i++) {
        vector<float>* ogMatrixCol = this->getColumn(i);
        tMatrix->insertRow(i, *ogMatrixCol);
    }

    return *tMatrix;
}












//Returns an 1 if the column augmentation was successful and a -1 if it wasnt successful
int Matrix::AugmentMatrix(Matrix &rhs) {
    if(rhs.getNumRows() == this->numRows){
        for(int i = 0; i < this->numRows; i++){
            for(int j = 0; j < rhs.getNumCols(); j++){
                matrix[i].push_back(rhs[i]->at(j));
            }
        }
        this->numCols += rhs.getNumCols();
        return 1;
    }
    else{
        std::cout<<"Matrix Augmentation failed"<<std::endl;
        return -1;
    }
}


void Matrix::print(){
    for(int i = 0; i < this->getNumRows(); i++){
        for(int j = 0; j < this->getNumCols(); j++){
            std::cout<<matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}








