#include "decryption.h"
#include "encryption.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <regex>
#include <cctype>
#include "multiplyCalculator.h"

bool valid_str(std::string select);
bool valid_returnMenu(std::string mainmenuSelection);
void encryptMenu();
void decryptMenu();

int main() {
  std::cout << "HILL CIPHER" << std::endl;
  bool valid_input = false;
  do {
    std::cout << "\nSelect E/e for Encryption or Select D/d for Decryption: ";
    std::string select;
    std::cin >> select;
    bool logic = valid_str(select);
    if (logic == true){
      if (select == "e" || select == "E"){
        encryptMenu();
      }
      else if (select == "d" || select == "D"){
        decryptMenu();
      }
      do {
        std::cout << "\nWould you like to go back to main menu? \nSelect 'Y' or 'y' for Yes or 'N' or 'n' for No : ";
        std::string mainmenuSelection;
        std::cin >> mainmenuSelection;
        bool logic1 = valid_returnMenu(mainmenuSelection);
        if (logic1 == true){
          if (mainmenuSelection == "Y" || mainmenuSelection == "y"){
            valid_input = false;
            break;
          }
          else if (mainmenuSelection == "N" || mainmenuSelection == "n"){
            valid_input = true;
            std::cout << "\nExit HILL CIPHER\n";
          }
        }
      } while (valid_input == false);
    }
    else {
      std::cout << "\nInvalid Input Selection.\n";
    }
  } while (valid_input == false);
  return 0;
}

bool valid_str(std::string select){
  return std::regex_match(select, std::regex("[DdEe]"));
}

bool valid_returnMenu(std::string mainmenuSelection){
  return std::regex_match(mainmenuSelection, std::regex("[YyNn]"));
}

void encryptMenu(){ 
  bool valid_plaintext = false;
  bool valid_key = false;
  bool input = false;
  std::string plaintext;
  std::string key;
  int plaintextLength;
  int matrixSize;
  int keyLength;
  do {
    std::cout << "\n-------Encryption Calculator---------\nType In Any Letter From A to Z";
    do {
      std::cout << "\nEnter plaintext : ";
      std::cin >> plaintext;
      // length of word in plaintext
      plaintextLength = plaintext.length();
      for (int i = 0; i < plaintextLength; i++){
        if ((isupper(plaintext[i]) && isalpha(plaintext[i])) != true){
          valid_plaintext = false;
          std::cout << "\nType in upper case alphabets only.\n";
          break;
        }
        else {
          valid_plaintext = true;
        }
      }
      

    } while (valid_plaintext == false);
    do {
    std::cout << "Enter key : ";
    std::cin >> key;
    // length of key text
    keyLength = key.length();
    for (int i = 0; i < keyLength; i++){
        if ((isupper(key[i]) && isalpha(key[i])) != true){
          valid_key = false;
          std::cout << "\nType in an upper case alphabets only.\n";
          break;
        }
        else {
          valid_key = true;
        }
      }  
    } while (valid_key == false);
    // size of n x n matrix
    matrixSize = keyLength / plaintextLength;
    if (matrixSize != plaintextLength){
      input = false;
      std::cout << "Length of Column key Matrix does not match with row of plaintext matrix\n";
    }
    else {
      input = true;
    }
  } while(input == false);
  
  // create a key matrix
  std::vector<std::vector<int>> keyMatrix;
  key_Matrix(key, matrixSize, keyMatrix);

  // create a plaintext matrix
  std::vector<int> plaintextMatrix;
  plTxt_Matrix(plaintext, matrixSize, plaintextMatrix);

  // matrix multiplication (key * plaintext % 26 = ciphertext)
  std::string finalResult = "(Key Matrix * Plaintext Matrix) % 26 :";
  MultiplyCalculator encryptionMultiply(keyMatrix, plaintextMatrix, matrixSize, finalResult);
  std::vector<int> ciphertextMatrix = encryptionMultiply.get_matrixMultiply();

  // create string variable that stores ciphertext
  std::string ciphertext;
  // convert matrix ciphertextMatrix to ciphertext
  cipherTxt(ciphertext, matrixSize, ciphertextMatrix);
  std::cout << "\nConvert Final Result Matrix to CipherText : \n" << ciphertext << "\n" << std::endl;

}

void decryptMenu(){
  std::string ciphertext;
  std::string key1;
  bool valid_ciphertext1 = false;
  bool valid_key1 = true;
  bool input1 = false;
  int ciphertextLength;
  int keyLength1;
  int matrixSize1;
  int determinant = 0;
  int invertDeterminant = 0;
  std::vector<std::vector<int>> keyMatrix1;
  do{
   std::cout << "\n-------Decryption Calculator---------\nType In Any Letter From A to Z";
  // using ciphertext = POH and key = GYBNQKURP
    do {
      std::cout << "\nEnter ciphertext (2 letters or 3 letters length): ";
      std::cin >> ciphertext;
      ciphertextLength = ciphertext.length();
      for (int i = 0; i < ciphertextLength; i++){
        if ((isupper(ciphertext[i]) && isalpha(ciphertext[i])) != true){
          valid_ciphertext1 = false;
          std::cout << "\nType in upper case alphabets only.\n";
          break;
        }
        else {
          valid_ciphertext1 = true;
        }
      }
    } while(valid_ciphertext1 == false);
    do {
      std::cout << "Enter key (4 letters or 9 letters length): ";
      std::cin >> key1;
      keyLength1 = key1.length();
      for (int i = 0; i < keyLength1; i++){
        if ((isupper(key1[i]) && isalpha(key1[i])) != true){
          valid_key1 = false;
          std::cout << "\nType in an upper case alphabets only.\n";
          break;
        }
        else {
          valid_key1 = true;
        }
      } 
    } while (valid_key1 == false);
    // size of n x n matrix
    matrixSize1 = keyLength1 / ciphertextLength;
    if (matrixSize1 != ciphertextLength){
      input1 = false;
      std::cout << "Length of column key matrix does not match with plaintext matrix row.\n";
    }
    else {
      input1 = true;
    }

  // create a 2d key matrix
  key_Matrix(key1, matrixSize1, keyMatrix1);
  
  // find inverse of 1/det for mod 26 operation
  invDet(matrixSize1, keyMatrix1, determinant, invertDeterminant);
  std::cout << "Determinant value = " << determinant << std::endl;
  std::cout << "Invert Determinent Value = " << invertDeterminant << std::endl;
  if (invertDeterminant == 0){
    input1 = false;
    std:: cout << "\nThe matrix is not invertible on mod 26.\n";
  }
} while(input1 == false);
  
  //To find Inverse key matrix, we need to find the adjoint matrix
  // transpose key matrix
  std::vector<std::vector<int>> transposeMatrix;
  if (matrixSize1 == 3){
  transpose(keyMatrix1, transposeMatrix, matrixSize1);
  }
  
  // find adjoint matrix (cofactor of each element) using tranpose key matrix
  std::vector<std::vector<int>> adjKeyMatrix;
  adjointMatrix(matrixSize1, adjKeyMatrix, transposeMatrix, keyMatrix1);

  // function to make sure all element of adjoint matrix are positive
  posAdjMatrix(matrixSize1, adjKeyMatrix);
  // inverseKeyMatrix = adjKeyMatrix * inverse determinent
  // inverseKeyMatrix % 26
  inverseKeyMatrix(matrixSize1, adjKeyMatrix, invertDeterminant);

  //--------------------------------------------------------
  // create a ciphertext matrix
  std::vector<int> cipher;
  formCipherTextMatrix(matrixSize1, cipher, ciphertext);
  
  //multiply inversematrix * ciphertext matrix % 26 = plaintext
  std::string finalResult1 = "(Inverse Matrix * Ciphertext Matrix) % 26";
  MultiplyCalculator decryptionMultiply(adjKeyMatrix, cipher, matrixSize1, finalResult1);
  std::vector<int> result = decryptionMultiply.get_matrixMultiply();

  //convert final result matrix value to characters and concatenate characters together
  std::string plaintext1;
  plaintextConversion(matrixSize1, result, plaintext1);
}