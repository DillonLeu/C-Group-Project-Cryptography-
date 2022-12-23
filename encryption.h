#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <iostream>
#include <vector>
void key_Matrix(std::string key, int matrixSize, std::vector<std::vector<int>> &keyMatrix);
void plTxt_Matrix(std::string plaintext, int matrixSize, std::vector<int> &plaintextMatrix);
void multiply_Matrix(int matrixSize, std::vector<std::vector<int>> &keyMatrix, std::vector<int> &plaintextMatrix, std::vector<int> &ciphertextMatrix);
void cipherTxt(std::string &ciphertext, int matrixSize, std::vector<int> &ciphertextMatrix);
#endif