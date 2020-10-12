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
using namespace std;

//function that does all the pageRanking which is used in main
void pageRanking() {
    int arrSize = 0; //size variable we change when reading file
    int* arr = readFile(&arrSize); //read values in and populate array
    matrix test = matrix(arr, arrSize); //pass in array and array size
    test.createProbabilityMatrix(); // create probability matrix
    double p = 0.85; //probability factor
    double t = 0.15; //teleport factor
    matrix m1 = test * p; //mulitply matrix by probability factor
    matrix teleportMatrix = matrix(arrSize, (1/sqrt(arrSize))); //create teleport matrix
    matrix m2 = teleportMatrix * t; //multiply teleport matrix by teleport factor
    matrix m = m1 + m2; //transition matrix is probability click links + probability teleport
    matrix rankMatrix = matrix(sqrt(arrSize), 1, 1); //create rank matrix
    matrix postMarkov = markov(m, rankMatrix); //markov the values based on m and rank until result converges
    postMarkov.getFinalRanks(); //print the final rank values
}

int * readFile(int * size) {

    ifstream myReadFile; //filestream being read
    myReadFile.open("connectivity.txt"); //open file
    double output; //blank double for reading
    int * numbers; //pointer for array
    numbers = new int[100]; //array we take in
    int count = 0; //initialize count to 0
    if (myReadFile.is_open()){ // if file opened
        while (myReadFile >> output)
        {
            numbers[count] = output; //read numbers into array
            count++;
        }

        *size = count; //change size variable to equal count

    }
    else { cout << "Error: File name not loaded" << endl;} //print error
    myReadFile.close();

    return numbers; //return pointer to array
}

matrix markov(matrix m, matrix rankMatrix) {

    //get first multiplication of m x rankmatrix
    matrix newM = (m * rankMatrix);

    //See if new matrix is in the range of the rank matrix
    while (!newM.compare(rankMatrix, 0.001)) {
        rankMatrix = newM; //new rank = newM
        newM = m * rankMatrix; //multiply m by rankmatrix
    }

    return newM; //return final new rankMatrix
}


