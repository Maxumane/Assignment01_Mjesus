//
// Created by Max on 2020-10-06.
//

#ifndef LAB05_MATRIX_HPP
#define LAB05_MATRIX_HPP
#include <iostream>
#include <vector>

using namespace std;

class matrix {
    int rows;
    int columns;
    double** matArr;

public:
    matrix(const matrix &otherMatrix);
    matrix();
    matrix(int n);
    matrix(int r, int c);
    matrix(double formArray[]);
    matrix(int r[], int arrSize);
    void setValue(int r, int c, int newValue);
    int getValue(int r, int c);
    void clear();
    matrix markov(matrix m, matrix rankMatrix);
    bool compare(matrix rhs, double tolerance);
    ~matrix();
    void createProbabilityMatrix();

    matrix operator++(int){
        matrix tmp(*this);
        operator++();
        return tmp;
    }

    matrix& operator=(matrix rhs) {
        mySwap(*this, rhs);
        return *this;
    }

    void mySwap(matrix &original, matrix &other) {
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                swap(original.matArr[i][j], other.matArr[i][j]);
            }
        }
    }

    matrix& operator++() {
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = (matArr[i][j] + 1);
            }
        }
        return *this;
    }

    matrix operator--(int){
        matrix tmp(*this);
        operator--();
        return tmp;
    }

    matrix& operator--() {
        for  (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matArr[i][j] = matArr[i][j] - 1;
            }
        }
        return *this;
    }

    matrix& operator+=(const matrix& rhs) {
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
