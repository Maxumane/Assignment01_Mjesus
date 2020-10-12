//
// Created by Max on 2020-10-06.
//

#include <iomanip>
#include "matrix.hpp"
#include <cmath>

matrix::matrix() :  rows(1), columns(1) {
    // Matrix default constructor initializes the rows and cols to be 1.
    matArr = new double*[rows]; //allocate new rows
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns]; //allocate new columns
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0.0; //initializes values to 0.
        }
    }
}

matrix::~matrix() {
    // Matrix destructor deletes dynamic memory.
    delete[]matArr;
}

matrix::matrix(const matrix& otherMatrix) {
    // Matrix copy constructor sets matrix variables to variables
    //of another matrix
    rows = otherMatrix.rows; //sets rows to the other matrixes rows
    columns = otherMatrix.columns; //sets columns to the other matrixes columns
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = otherMatrix.matArr[i][j]; //set values to other matrix values
        }
    }
}


matrix::matrix(int n) : rows(n), columns(n) {
    //creates an array of n x n of 0's
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0; //set values to 0.
        }
    }
}

matrix::matrix(int r, int c) : rows(r), columns(c) {
    //creates an array of r x c
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0; //set values to 0.
        }
    }
}

matrix::matrix(int r[], int arrSize) {

    //get squareRoot of arrsize to use for rows and cols
    double sizeRoot = sqrt(arrSize);

    //check if arraySize is compatible
    if ((sizeRoot - floor(sizeRoot)) != 0) {
        throw std::invalid_argument("Array size does not have"
                                    "an integer square root!");
    }

    int rootInd = (int) sizeRoot; //convert sizeRoot to int

    rows = rootInd;
    columns = rootInd;


    matArr = new double*[rows];
    int index = 0;

    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    //parse through array and make it an indexed value of the array
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = r[index++];
        }
    }
}

void matrix::setValue(int r, int c, int newValue) {
    matArr[r-1][c-1] = newValue;
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
        }
    }
}

int matrix::getValue(int r, int c) {
    //check if value being looked for is in the matrix range
    if (rows < r || rows < 0 || columns < c || columns < 0) {
        throw std::invalid_argument("Entered indexes are invalid!");
    }
    cout << matArr[r-1][c-1] << " ";
    return matArr[r-1][c-1];
}

void matrix::clear() {
    // change all values to 0 of a matrix
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = 0;
        }
    }
}

void matrix::createProbabilityMatrix() {
    //set variable count to 0
    int count = 0;
            for  (int i = 0; i < columns; i++) {
                count = 0;

                //get the count of 1s in a column
                for (int j = 0; j < rows; j++) {
                    if (matArr[j][i] == 1) {
                        count++;
                    }
                }

                //get the probability by dividing 1s by count of 1s
                for (int j = 0; j < rows; j++) {
                    if (matArr[j][i] == 1) {
                        matArr[j][i] = (matArr[j][i] / count);
                    }
                    //if column is full of zeroes have the values add up
                    //to equal 1
                    if (count == 0) {
                        matArr[j][i] =  (((double) 1) / ((double) rows));
                    }
                }
            }
}

void matrix::getFinalRanks() {
    //Display final ranks
    cout << "Final ranks below:" << endl;
    double total = 0;
    for  (int i = 0; i < columns; i++) {
        total = 0;

        //collect total of final rank values
        for (int j = 0; j < rows; j++) {
            total += matArr[j][i];
        }

        //Display rank values as percents
        for (int j = 0; j < rows; j++) {
                cout << ((matArr[j][i] / total) * (double) 100) << "%" << endl;
        }
    }
}

ostream& operator<< (ostream& os, const matrix& a) {
    //change ostream operator to display matricies in
    // matrix format
    for  (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            os << a.matArr[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

bool operator== (const matrix &lhs, const matrix &rhs) {
    //check if matricies have the same values
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return false;
    }
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            //check if theres a discrepancy in the value
            if (lhs.matArr[i][j] != rhs.matArr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!= (const matrix &lhs, const matrix &rhs) {
    //if matricies arent the same size
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return true;
    }
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            //check if theres a discrepancy in the value
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
            //parse matrixes and check if the corresponding values are outside the tolerance range
            if (!abs(this->matArr[i][j] - rhs.matArr[i][j]) <= tolerance) {
                return false;
            }
        }
    }
    return true;
}

matrix::matrix(int n, double value) {
    // creates matrix of n x n
    rows = sqrt(n);
    columns = sqrt(n);
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = value; //change all values to value
        }
    }
}

matrix::matrix(int r, int c, double value) {
    //creates a matrix of r X c and fill it with value
    rows = r;
    columns = c;
    matArr = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matArr[i] = new double[columns];
    }
    for  (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matArr[i][j] = value; //change all values to value
        }
    }
}



matrix& matrix::operator*=(const matrix &rhs) {
    // throw exception if matricies cannot be multiplied
    if (columns != rhs.rows) {
        throw std::invalid_argument("Entered indexes are invalid!");
    }

    //determine product matrix columns by finding the lower column value
    int prodCol = (columns < rhs.columns) ? columns : rhs.columns;
    //determine product matrix rows by finding the lower rows value
    int prodRow = (rows < rhs.columns) ? rows : rhs.rows;

    matrix product = matrix(prodRow, prodCol);

    for (int i = 0; i < prodRow; i++) {
        for (int j = 0; j < prodCol; j++) {
            for (int k = 0; k < columns; k++) {
                // multiply each matrix value in the order of matrix multiplication
                product.matArr[i][j] += matArr[i][k] * rhs.matArr[k][j];
            }
        }
    }
    //Set the following values of the matrix
    //to the product matrix through pointing
    this->matArr = product.matArr;
    this->columns = prodCol;
    this->rows = prodRow;
    this->matArr = product.matArr;
    product.matArr = nullptr;
    return *this;
}

matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs; //uses += operator
    return lhs; // returns copy of altered lhs
}
matrix operator-(matrix lhs, const matrix& rhs) {
    lhs -= rhs; //uses -= operator
    return lhs; // returns copy of altered lhs
}

matrix operator*(matrix lhs, const matrix& rhs) {
    lhs *= rhs; //uses *= operator
    return lhs; //returns copy of altered lhs
}

matrix operator*(matrix lhs, double n) {
    for  (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.columns; j++) {
            lhs.matArr[i][j] = (lhs.matArr[i][j] * n); // multiples each number by n
        }
    }
    return lhs; //return altered lhs
}



