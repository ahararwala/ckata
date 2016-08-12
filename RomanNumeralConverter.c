#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralConverter.h"

int toNumeric(int * result, const char* roman) {
  * result = 1;
  return validateRomanNumeral(roman);
}

int validateRomanNumeral(const char* roman) {
  int trackContigousOccrances=0;
  int i = 0;
  char candidate = roman[i];
  while (roman[i] != '\0') {
      if (roman[i] == candidate) {
        trackContigousOccrances = trackContigousOccrances+1;
      } else {
        candidate = roman[i];
        trackContigousOccrances = 1;
      }
      int code = validate(trackContigousOccrances, roman[i]);
      if (code == INVALID_ROMAN_ERROR_CODE) {
        return INVALID_ROMAN_ERROR_CODE;
      }
      i++;
  }
	return SUCCESS_CODE;
}

int validate(int actualOccurances, char roman) {
      int allowedContiguousOccurrances = getRuleFor(roman);
      // printf("roman=%c, rule=%d, actualOccurances=%d\n", roman, allowedContiguousOccurrances, actualOccurances);
      if (allowedContiguousOccurrances == SUCCESS_CODE) {
        return SUCCESS_CODE;
      }

      if (actualOccurances > allowedContiguousOccurrances) {
          return INVALID_ROMAN_ERROR_CODE;
      }
      return SUCCESS_CODE;
}

int getRuleFor(char roman) {
  if (roman == 'I') {
    return 3;
  }
  if (roman == 'X') {
    return 3;
  }
  if (roman == 'C') {
    return 3;
  }

  return SUCCESS_CODE;
}
