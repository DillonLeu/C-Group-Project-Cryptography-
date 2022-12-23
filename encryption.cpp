#include "encryption.h"

// create key matrix
void key_Matrix(std::string key, int matrixSize, std::vector<std::vector<int>> &keyMatrix) {
  // inc is created to go through every character stored in key string
  int inc = 0;
  for (int i = 0; i < matrixSize; i++) {
    std::vector<int> innerKeyMatrix;
    for (int j = 0; j < matrixSize; j++){
      innerKeyMatrix.push_back(key[inc] % 65);
      inc++;
    }
    keyMatrix.push_back(innerKeyMatrix);
  }
  // print out key matrix
  std::cout << "\nKey Matrix :\n";
  for (int i = 0; i < matrixSize; i++) {
      std::cout << "| ";
      for (int j = 0; j < matrixSize; j++) {
        std::cout << keyMatrix[i][j] << " ";
      }
      std::cout << " |" << std::endl;
  }
  std::cout << std::endl;
}

// create plaintext matrix
void plTxt_Matrix(std::string plaintext, int matrixSize, std::vector<int> &plaintextMatrix){
  for (int i = 0; i < matrixSize; i++){
    plaintextMatrix.push_back(plaintext[i] % 65);
  }
  // print plaintext matrix
  std::cout << "Plaintext Matrix :\n";
  for (int i = 0; i < matrixSize; i++) {
    std::cout << "| " << plaintextMatrix[i] << " |" << std::endl;
  }
  std::cout << std::endl;
}

// convert ciphertext matrix sotring int values back to character and concatenate into a string variable
void cipherTxt(std::string &ciphertext, int sizeMatrix, std::vector<int> &ciphertextMatrix){
for (int i = 0; i < sizeMatrix; i++){
    ciphertext += char(ciphertextMatrix[i]+ 65);
  }
}