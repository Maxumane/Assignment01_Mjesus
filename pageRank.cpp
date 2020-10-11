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
const char *targetfile = "readings.txt";
using namespace std;
const int MAX_SIZE = 100;

void pageRanking() {
    int arrSize = 0;
    int* arr = readFile(&arrSize);
    cout << "array size: " << arrSize << endl;
    matrix test = matrix(arr, arrSize);
    test.createProbabilityMatrix();
    matrix s = test * 0.85;
    cout << s;
//    matrix rankMatrix = generateRankMatrix();
//    s.markov()
}

int * readFile(int * size) {

    ifstream myReadFile;
    myReadFile.open("readings.txt");
    double output;
    int * numbers;
    numbers = new int[100];
    int count = 0;
    if (myReadFile.is_open()){
        while (myReadFile >> output && !myReadFile.eof())
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

