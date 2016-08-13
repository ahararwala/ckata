#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralCalculator.h"
#include "RomanNumeralConverter.h"

int isError(int exitCode);

int addRomanNumerals(char* output, const char* roman1, const char* roman2){
  int exitCode;
  int num1;
  int num2;

  exitCode = toNumeric(&num1, roman1);
  if (isError(exitCode)) {
    return exitCode;
  }
  exitCode = toNumeric(&num2, roman2);
  if (isError(exitCode)) {
    return exitCode;
  }
  int sum = num1 + num2;
  if (sum > MAX_ROMAN_NUMERAL_VALUE) {
    return INVALID_ROMAN_ERROR_CODE;
  }
  return toRoman(output, sum);
}

int isError(int code) {
  if (code == INVALID_ROMAN_ERROR_CODE) {
    return code;
  }
  return SUCCESS_CODE;
}
int subtractRomanNumerals(char* output, const char* roman1, const char* roman2){
  return 0;
}
