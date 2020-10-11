//
// Created by Max on 2020-10-10.
//

#include "pageRank.hpp"
#include <fstream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "matrix.hpp"
#include <cmath>
const char *targetfile = "readings.txt";
using namespace std;
const int MAX_SIZE = 100;

void pageRanking() {
    int arrSize = 0;
    int* arr = readFile(&arrSize);
    cout << "array size: " << arrSize << endl;
    matrix test = matrix(arr, arrSize);
    test.createProbabilityMatrix();
    matrix m1 = test * 0.85;
    cout << m1;
    matrix teleportMatrix = matrix(arrSize, (1/sqrt(arrSize)));
    matrix m2 = teleportMatrix * 0.15;
    matrix m = m1 + m2;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    cout << m;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    cout << "printRank" << endl;
    matrix rankMatrix = matrix(sqrt(arrSize), 1, 1);
    cout << rankMatrix << endl;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    matrix testMultiply = test * rankMatrix;
    cout << test;
    cout << "//////////////" << endl;
    cout << testMultiply;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    cout << "//////////////" << endl;
    matrix postMarkov = markov(m, rankMatrix);
    cout << postMarkov << endl;
//    matrix newM = test * test;
}

int * readFile(int * size) {

    ifstream myReadFile;
    myReadFile.open("readings.txt");
    double output;
    int * numbers;
    numbers = new int[100];
    int count = 0;
    if (myReadFile.is_open()){
        while (myReadFile >> output)
        {
            numbers[count] = output;
            count++;
        }

        *size = count;

        for(int i = 0; i < count; i++)
        {
            cout << numbers[i] << endl;
        }
    }
    else { cout << "Error: File name not loaded" << endl;}
    myReadFile.close();

    return numbers;
}

matrix markov(matrix m, matrix rankMatrix) {

    matrix newM = (m * rankMatrix);


    while (!newM.compare(rankMatrix, 0.001)) {
        rankMatrix = newM;
        newM = m * rankMatrix;
    }

    return newM;
}

void addItUp() {

}

