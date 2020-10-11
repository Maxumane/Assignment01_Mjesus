//
// Created by Max on 2020-10-10.
//
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "matrix.hpp"

#ifndef ASSIGNMENT01_MJESUS_PAGERANK_HPP
#define ASSIGNMENT01_MJESUS_PAGERANK_HPP

using namespace std;

int * readFile(int * size);
void pageRanking();
matrix markov(matrix m, matrix rankMatrix);

#endif //ASSIGNMENT01_MJESUS_PAGERANK_HPP
