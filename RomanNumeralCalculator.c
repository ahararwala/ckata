#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralCalculator.h"
#include "RomanNumeralConverter.h"

typedef enum {
  Addition,
  Subtraction
} Operation;

int computeRomanNumerals(char* output, Operation  operationToPerform, const char* roman1, const char* roman2);
int performOperation(Operation operationToPerform, int num1, int num2);
int isError(int exitCode);

int addRomanNumerals(char* output, const char* roman1, const char* roman2){
  return computeRomanNumerals(output, Addition, roman1, roman2);
}

int subtractRomanNumerals(char* output, const char* roman1, const char* roman2){
  return computeRomanNumerals(output, Subtraction, roman1, roman2);
}

int computeRomanNumerals(char* output, Operation  operationToPerform, const char* roman1, const char* roman2){
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
  int computedValue = performOperation(operationToPerform, num1, num2);
  if (computedValue > MAX_ROMAN_NUMERAL_VALUE || computedValue <= 0) {
    return INVALID_ROMAN_ERROR_CODE;
  }
  return toRoman(output, computedValue);
}
int performOperation(Operation operationToPerform, int num1, int num2) {
  int computedValue;
  if (operationToPerform == Addition) {
    computedValue = num1 + num2;
  } else if (operationToPerform == Subtraction) {
    computedValue = num1 - num2;
  }
  return computedValue;
}

int isError(int code) {
  if (code == INVALID_ROMAN_ERROR_CODE) {
    return code;
  }
  return SUCCESS_CODE;
}
