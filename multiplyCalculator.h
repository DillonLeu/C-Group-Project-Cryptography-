#ifndef MULTIPLYCALCULATOR_H
#define MULTIPLYCALCULATOR_H
#include <vector>
#include <iostream>
class MultiplyCalculator {
public:
//constructor with values
MultiplyCalculator(std::vector<std::vector<int>> key, std::vector<int> text, int matrixSize, std::string finalResult);
std::vector<int> get_matrixMultiply();
private:
std::vector<std::vector<int>> _key;
std::vector<int> _text;
std::vector<int> _result;
int _matrixSize;
std::string _finalResult;
};

#endif