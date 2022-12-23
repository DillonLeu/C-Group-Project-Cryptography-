#include "decryption.h"
//void invDet(int &determinant, int &invertDeterminant){ 
//find inverse of 1/det for mod 26
void invDet(int matrixSize1, std::vector<std::vector<int>> keyMatrix1, int &determinant, int &invertDeterminant){ 
  // for 1 x 1 matrix key(1 letter) and 2 x 2 matrix key(4 letters)
  if (matrixSize1 == 1 || matrixSize1 == 2) {
    detmatrix(matrixSize1, keyMatrix1, determinant);
  } 
  // for 3 x 3 matrix key(9 letters)
  else if (matrixSize1 == 3) {
    det3x3(matrixSize1, keyMatrix1, determinant);
  }

  //if the determinant is a negative number, then execute this if statement
  if (determinant < 0){
    determinant = determinant % 26;
    if (determinant < 0){
      determinant = determinant + 26;
    }
  }
  int i = 1;
  while (i >= 1) {
    int num = (determinant * i) % 26;
    if (num == 1){
      invertDeterminant = i;
      break;
    }
    i++;
  }
}

void detmatrix(int matrixSize1, std::vector<std::vector<int>> keyMatrix1, int &determinant) {
    // 1 x 1 matrix key(1 letter) 
    if (matrixSize1 == 1) {
      determinant = keyMatrix1[0][0];
      if(determinant == 0){
        std::cout << "This matrix cannot be used in the Hill Cipher." << std::endl;
      }
    }
    // 2 x 2 matrix key(4 letters)
    else if (matrixSize1 == 2) {
      int a, b, c, d;
      a = keyMatrix1[0][0];
      b = keyMatrix1[0][1];
      c = keyMatrix1[1][0];
      d = keyMatrix1[1][1];
      determinant = a * d - b * c;
    }
}

// find determinant for 3 by 3 matrix(12 letters)
void det3x3(int matrixSize1, std::vector<std::vector<int>> keyMatrix1, int &determinant){
  std::vector<std::vector<int>> primaryMatrix;
  std::vector<int> secondaryMatrix;
  int sign = 1;
  for (int col = 0; col < matrixSize1; col++){ 
  
    for (int r = 0; r < matrixSize1; r++){
      for (int c = 0; c < matrixSize1; c++){
        if (r != 0 && c != col){
          secondaryMatrix.push_back(keyMatrix1[r][c]);
          if (secondaryMatrix.size() == matrixSize1 - 1){
            primaryMatrix.push_back(secondaryMatrix);
            secondaryMatrix.clear();
          }
        }
      }
    }
    //print out 2x2 matrix formed when first row column shifted
    for (int i = 0; i < matrixSize1-1; i++){
    std::cout << "| ";
    for (int j = 0; j < matrixSize1-1; j++){
    std::cout << primaryMatrix[i][j] << " ";
    }
    std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
  determinant += sign * keyMatrix1[0][col] * matrixSize2(primaryMatrix);
  sign = -sign;
  primaryMatrix.clear();
  }
}

// 2x2 matrix inside 3x3 matrix
int matrixSize2(std::vector<std::vector<int>> &matrix2x2){
  int a, b, c, d, value;
  a = matrix2x2[0][0];
  b = matrix2x2[0][1];
  c = matrix2x2[1][0];
  d = matrix2x2[1][1];
  value = a * d - b * c;
  return value;
}


// tranpose key matrix
void transpose(std::vector<std::vector<int>> keyMatrix1, std::vector<std::vector<int>> &transposeMatrix, int matrixSize1){
  std::vector<int> innerTransposeMatrix;
  for (int i = 0; i < matrixSize1; i++){
    innerTransposeMatrix.clear();
    for (int j = 0; j < matrixSize1; j++){
       innerTransposeMatrix.push_back(keyMatrix1[j][i]);
       if (innerTransposeMatrix.size() == matrixSize1){
         transposeMatrix.push_back(innerTransposeMatrix);
        }
    }
  }
  // print transpose key matrix
  std::cout << "\nTranspose Key Matrix: \n";
  for (int i = 0; i < matrixSize1; i++){
    std::cout << "| ";
    for (int j = 0; j < matrixSize1; j++){
    std::cout << transposeMatrix[i][j] << " ";
    }
    std::cout << " |" << std::endl;
  }
}

// find adjoint of square matrix
void adjointMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix, std::vector<std::vector<int>> transposeMatrix, std::vector<std::vector<int>> keyMatrix1){
std::vector<std::vector<int>> matrix;
std::vector<int> innerMatrix;
std::vector<int> cofactor;
int sign = 1;
int a, b, c, d;
if (matrixSize1 == 1){
  innerMatrix.push_back(keyMatrix1[0][0]);
  adjKeyMatrix.push_back(innerMatrix);
  innerMatrix.clear();
}
if (matrixSize1 == 2){
  for (int i = 0; i <  matrixSize1; i++){
    for (int j = 0; j < matrixSize1; j++){
      if (i == 0 && j == 0){
        innerMatrix.push_back(keyMatrix1[1][1]);
      }
      else if (i == 1 && j == 1){
        innerMatrix.push_back(keyMatrix1[0][0]);
      }
      else if (i != j){
        b = -sign * keyMatrix1[i][j];
        innerMatrix.push_back(b);
      }
      if (innerMatrix.size() == matrixSize1){
        adjKeyMatrix.push_back(innerMatrix);
        innerMatrix.clear();
      }
    }
  }
}

else if (matrixSize1 == 3){
  for (int i = 0; i < matrixSize1; i++){
    for (int j = 0; j < matrixSize1; j++){
      for (int row = 0; row < matrixSize1; row++){
        for (int col = 0; col < matrixSize1; col++){
          if (row != i && col != j){
            innerMatrix.push_back(transposeMatrix[row][col]);
            if (innerMatrix.size() == matrixSize1 - 1){
              matrix.push_back(innerMatrix);
              innerMatrix.clear();
            }
          }
        }
      }
      int sum = 0;
      a = matrix[0][0];
      b = matrix[0][1];
      c = matrix[1][0];
      d = matrix[1][1];
      sum = sign * (a*d - b*c);
      sign = -1 * sign;
      cofactor.push_back(sum);
      if (cofactor.size() == matrixSize1){
        adjKeyMatrix.push_back(cofactor);
        cofactor.clear();
      }
      matrix.clear();
    }
  }
}
  std::cout << "\nAdjoint matrix : \n";
  for (int i = 0; i < matrixSize1; i++){
    std::cout << "| ";
    for (int j = 0; j < matrixSize1; j++){
      std::cout << adjKeyMatrix[i][j] << " ";
    }
    std::cout << " |" << std::endl;
  }
}


// getting rid of negative number for adjoint matrix
void posAdjMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix){
  for (int i = 0; i < matrixSize1; i++){
    for (int j = 0; j < matrixSize1; j++){
      if (adjKeyMatrix[i][j] < 0){
        int ans = 0;
        while(ans >= 0){
          if (adjKeyMatrix[i][j] + (ans * 26) > 0){
            int value = adjKeyMatrix[i][j] + (ans * 26);
            adjKeyMatrix[i][j] = value;
            break;
          }
          ans = ans + 1;
        }
      }
    }
  }
  // print positive adjugate matrix
  std::cout << "\nConvert Elements in Adjoint Matrix to Positive :\n";
  for (int i = 0; i < matrixSize1; i++){
    std::cout << "| ";
    for (int j = 0; j < matrixSize1; j++){
      std::cout << adjKeyMatrix[i][j] << " ";
    }
    std::cout << " |" << std::endl; 
  }
}


// multiply posAdjMatrix by invertDeterminant to get the inverse key matrix and then replace each element with the remainder value when divide by 26
void inverseKeyMatrix(int matrixSize1, std::vector<std::vector<int>> &adjKeyMatrix, int invertDeterminant){
  for (int i = 0; i < matrixSize1; i++){
    for (int j = 0; j < matrixSize1; j++){
      adjKeyMatrix[i][j] = (adjKeyMatrix[i][j] * invertDeterminant) % 26;
    }
  }
  // print final result of adjoint matrix
  std::cout << "\nInverse Key Matrix % 26 :\n";
  for (int i = 0; i < matrixSize1; i++){
    std::cout << "| ";
    for (int j = 0; j <matrixSize1; j++){
      std::cout << adjKeyMatrix[i][j] << " ";
    }
    std::cout << " |" << std::endl; 
  }
}

void formCipherTextMatrix(int matrixSize1, std::vector<int> &cipher1, std::string ciphertext1){
  for (int i = 0; i < matrixSize1; i++){
    cipher1.push_back(ciphertext1[i] % 65);
  }
}

void plaintextConversion(int matrixSize1, std::vector<int> result, std::string &plaintext1){
  for (int i = 0; i < matrixSize1; i++){
    plaintext1 += char(result[i]+65);
    }
  std::cout << "\nPlaintext = "<< plaintext1 << std::endl;
}
