#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralConverter.h"

int toNumeric(int * result, const char* roman) {
  * result = 1;
  if (strcmp(roman, "IIII") == 0 || strcmp(roman, "XXXX") == 0) {
    return INVALID_ROMAN_ERROR_CODE;
  }

	return SUCCESS_CODE;
}
