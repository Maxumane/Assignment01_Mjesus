//
// Created by Max on 2020-10-06.
//

#include <iomanip>
#include "matrix.hpp"
#include <cmath>

matrix::matrix() :  rows(1), columns(1) {
    //when making copy construct, change rows and cols to othermatrix rows and cols
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0.0; // change this to equal othermatrix values
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

matrix::~matrix() {
    delete[]matArr;
}

matrix::matrix(const matrix& otherMatrix) {
    rows = otherMatrix.rows;
    columns = otherMatrix.columns;
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = otherMatrix.matArr[i][j];
        }
    }
}


matrix::matrix(int n) : rows(n), columns(n) {
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0;
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

matrix::matrix(int r, int c) : rows(r), columns(c) {
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0;
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

//matrix m;

//matrix markov(matrix m, matrix rankMatrix) { MARKOV
//
//    matrix newM = m * rankMatrix
//
//    while (compare(newM, rankMatrix, 0.01)) {
//        rankMatrix = newM;
//        newM = m * rankMatrix;
//    }
//
//    return newM;
//}
//
//matrix finalAnswer = markov(m, rankMatrix);


matrix matrix::markov(matrix m, matrix rankMatrix) {

        matrix newM = m * rankMatrix;

        while (newM.compare(rankMatrix, 0.01)) {
            rankMatrix = newM;
            newM = m * rankMatrix;
        }

        return newM;
}

matrix::matrix(int r[], int arrSize) {

    double sizeRoot = sqrt(arrSize);


    if ((sizeRoot - floor(sizeRoot)) != 0) {
        throw std::invalid_argument("Array size does not have"
                                    "an integer square root!");
    }

    int rootInd = (int) sizeRoot;

    rows = rootInd;
    columns = rootInd;



    matArr = new double*[rows];
    int index = 0;

    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = r[index++];
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

void matrix::setValue(int r, int c, int newValue) {
    matArr[r-1][c-1] = newValue;
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

int matrix::getValue(int r, int c) {
    if (rows < r || rows < 0 || columns < c || columns < 0) {
        throw std::invalid_argument("Entered indexes are invalid!");
    }
    cout << matArr[r-1][c-1] << " ";
    return matArr[r-1][c-1];
}

void matrix::clear() {
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0;
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

void matrix::createProbabilityMatrix() {
    cout << "generating probability matrix" << endl;
    int count = 0;
            for  (int i = 0; i < columns; i++) {
                count = 0;

                for (int j = 0; j < rows; j++) {
                    if (matArr[j][i] == 1) {
                        count++;
                    }
                }

                for (int j = 0; j < rows; j++) {
                    if (matArr[j][i] == 1) {
                        matArr[j][i] = (matArr[j][i] / count);
                    }
                    if (count == 0) {
                        matArr[j][i] =  (((double) 1) / ((double) rows));
                    }
                }
            }
}

ostream& operator<< (ostream& os, const matrix& a) {
    for  (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            os << fixed << setprecision(3) << a.matArr[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

bool operator== (const matrix &lhs, const matrix &rhs) {
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return false;
    }
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            if (lhs.matArr[i][j] != rhs.matArr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!= (const matrix &lhs, const matrix &rhs) {
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return true;
    }
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            if (lhs.matArr[i][j] != rhs.matArr[i][j]) {
                return true;
            }
        }
    }
    return false;
}


bool matrix::compare(matrix rhs, double tolerance) {
    if(this->rows != rhs.rows || this->columns != rhs.columns) {
        return false;
    }
    for  (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (!(this->matArr[i][j] <= (rhs.matArr[i][j] + tolerance)) && !(this->matArr[i][j] >= (rhs.matArr[i][j] - tolerance))) {
                return false;
            }
        }
    }
    return true;
}

matrix::matrix(int n, double value) {
    rows = sqrt(n);
    columns = sqrt(n);
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = value;
            cout << fixed << setprecision(3) << matArr[i][j] << " ";
        }
        cout << endl;
    }
}

matrix::matrix(int r, int c, double value) {
    rows = r;
    columns = c;
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = value;
        }
    }
}



matrix& matrix::operator*=(const matrix &rhs) {
    if (columns != rhs.rows) {
        throw std::invalid_argument("Entered indexes are invalid!");
    }

    cout << "starting multiply" << endl;

    int prodCol = (columns < rhs.columns) ? columns : rhs.columns;
    int prodRow = (rows < rhs.columns) ? rows : rhs.rows;

    cout << "rows: " << prodRow << endl;
    cout << "columns: " << prodCol << endl;

    matrix product = matrix(prodRow, prodCol);

    for (int i = 0; i < prodRow; i++) {
        for (int j = 0; j < prodCol; j++) {
            for (int k = 0; k < columns; k++) {
                product.matArr[i][j] += matArr[k][j] * rhs.matArr[i][k];
                cout << matArr[k][j] * rhs.matArr[i][k] << " ";
            }
        }
        cout << endl;
    }
    this->matArr = product.matArr;
    product.matArr = nullptr;
    return *this;
}

matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}
matrix operator-(matrix lhs, const matrix& rhs) {
    lhs -= rhs;
    return lhs;
}

matrix operator*(matrix lhs, const matrix& rhs) {
    lhs *= rhs;
    return lhs;
}

matrix operator*(matrix lhs, double n) {
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            lhs.matArr[i][j] = (lhs.matArr[i][j] * n); // change this to equal othermatrix values
        }
    }
    return lhs;
}



