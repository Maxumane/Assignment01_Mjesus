//
// Created by Max on 2020-10-06.
//

#ifndef LAB05_MATRIX_HPP
#define LAB05_MATRIX_HPP
#include <iostream>
#include <vector>

using namespace std;

class matrix {
    int rows; //rows of matrix
    int columns; //columns of matrix
    double** matArr; //double ** to matrix array

public:
    matrix(const matrix &otherMatrix);
    matrix();
    matrix(int n);
    matrix(int r, int c);
    matrix(int r, int c, double value);
    matrix(double formArray[]);
    matrix(int r[], int arrSize);
    matrix(int n, double value);
    void setValue(int r, int c, int newValue);
    int getValue(int r, int c);
    void clear();
    void getFinalRanks();
    bool compare(matrix rhs, double tolerance);
    ~matrix();
    void createProbabilityMatrix();

    matrix operator++(int){
        //use operator to increment and return original:postfix
        matrix tmp(*this);
        operator++();
        return tmp;
    }

    matrix& operator=(matrix rhs) {
        //copy and swap algorithm
        mySwap(*this, rhs);
        return *this;
    }

    void mySwap(matrix &original, matrix &other) {
        //parse array and swap values
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                swap(original.matArr[i][j], other.matArr[i][j]);
            }
        }
    }

    matrix& operator++() {
        //increment all matrix values by 1
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = (matArr[i][j] + 1);
            }
        }
        return *this;
    }

    matrix operator--(int){
        //use operator to increment and return original:postfix
        matrix tmp(*this);
        operator--();
        return tmp;
    }

    matrix& operator--() {
        //decrement all matrix values by 1
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = matArr[i][j] - 1;
            }
        }
        return *this;
    }

    matrix& operator+=(const matrix& rhs) {
        //parse matrix and add other matrix's corresponding value

        if (rows != rhs.rows || columns != rhs.columns) {
            throw std::invalid_argument("Entered indexes are invalid!");
        }
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = matArr[i][j] + rhs.matArr[i][j];
            }
        }
        return *this;
    }




    matrix& operator-=(const matrix& rhs) {
        if (rows != rhs.rows || columns != rhs.columns) {
            throw std::invalid_argument("Entered indexes are invalid!");
        }
        //parse matrix and subtract other matrix's corresponding value
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = matArr[i][j] - rhs.matArr[i][j];
            }
        }
        return *this;
    }

    matrix& operator*=(const matrix& rhs);
    friend matrix operator*(matrix lhs, double n);
    friend matrix operator*(matrix lhs, const matrix& rhs);
    friend matrix operator-(matrix lhs, const matrix& rhs);
    friend matrix operator+(matrix lhs, const matrix& rhs);
    friend std::ostream& operator<<(std::ostream&, const matrix&);
    friend bool operator== (const matrix &lhs, const matrix &rhs);
    friend bool operator!= (const matrix &lhs, const matrix &rhs);
};
#endif //LAB05_MATRIX_HPP

