#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralCalculator.h"
#include "RomanNumeralConverter.h"

int addRomanNumerals(char* output, const char* roman1, const char* roman2){
  int exitCode;
  int num1;
  int num2;

  exitCode = toNumeric(&num1, roman1);
  exitCode = toNumeric(&num2, roman2);

  int sum = num1 + num2;
  // printf("summation=%d\n", sum);

  exitCode = toRoman(output, sum);
  return exitCode;
}

int subtractRomanNumerals(char* output, const char* roman1, const char* roman2){
  return 0;
}
