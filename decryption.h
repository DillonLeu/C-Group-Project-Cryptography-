#ifndef DECRYPTION_H
#define DECRYPTION_H
#include <iostream>
#include <vector>
void invDet(int matrixSize1, std::vector<std::vector<int>> keyMatrix1, int &determinant, int &invertDeterminant);
void detmatrix(int sizeMatrix1, std::vector<std::vector<int>> keyMatrix1, int &determinant);
void det3x3(int sizeMatrix1, std::vector<std::vector<int>> keyMatrix1, int &determinant);
int matrixSize2(std::vector<std::vector<int>> &matrix2X2);


void transpose(std::vector<std::vector<int>> keyMatrix1, std::vector<std::vector<int>> &transposeMatrix, int matrixSize1);
void adjointMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix, std::vector<std::vector<int>> transposeMatrix, std::vector<std::vector<int>> keyMatrix1);
void posAdjMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix);
void inverseKeyMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix, int invertDeterminant);
void formCipherTextMatrix(int matrixSize1, std::vector<int> &cipher1, std::string ciphertext1);
void plaintextConversion(int matrixSize1, std::vector<int> result, std::string &plaintext1);
#endif
