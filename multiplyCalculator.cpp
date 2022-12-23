#include "multiplyCalculator.h"
#include <iostream>
//initialise constructor
MultiplyCalculator::MultiplyCalculator(std::vector<std::vector<int>> key, std::vector<int> text, int matrixSize, std::string finalResult) { _key = key; _text = text; _matrixSize = matrixSize; _finalResult = finalResult; }
std::vector<int> MultiplyCalculator::get_matrixMultiply() {
  for (int i =0; i < _matrixSize; i++){
    int sum = 0;
    for (int j = 0; j < _matrixSize; j++){
      sum += _text[j] * _key[i][j];
    }
    _result.push_back(sum);
  }
  for (int i = 0; i < _matrixSize; i++){
     _result[i] = _result[i] % 26;
   }
  std::cout << "\n" << _finalResult << "\n";
  for (int i = 0; i < _matrixSize; i++){
    std::cout << "| ";
    std::cout << _result[i];
    std::cout << " |" << std::endl; 
  }

  return _result;
}
