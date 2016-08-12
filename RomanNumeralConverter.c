#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralConverter.h"
struct KeyValuePair {
     char *key;
     int value;
};

const struct KeyValuePair ROMAN_NUMERALS_SEQUENCE_RULE[6] = {{"I", 3}, {"X", 3}, {"C", 3}, {"V", 1}, {"L",1}, {"D", 1}};

int toNumeric(int * result, const char* roman) {
  * result = 1;
  return validateRomanNumeral(roman);
}

int validateRomanNumeral(const char* roman) {
  int trackContiguousOccurrences=0;
  int i = 0;
  char candidate = roman[i];
  while (roman[i] != '\0') {
      if (roman[i] == candidate) {
        trackContiguousOccurrences = trackContiguousOccurrences+1;
      } else {
        candidate = roman[i];
        trackContiguousOccurrences = 1;
      }
      int code = validate(trackContiguousOccurrences, roman[i]);
      if (code == INVALID_ROMAN_ERROR_CODE) {
        return INVALID_ROMAN_ERROR_CODE;
      }
      i++;
  }
	return SUCCESS_CODE;
}

int validate(int actualOccurances, char roman) {
    int allowedContiguousOccurrences = getRuleFor(roman);
    if (allowedContiguousOccurrences == SUCCESS_CODE) {
      return SUCCESS_CODE;
    }

    if (actualOccurances > allowedContiguousOccurrences) {
        return INVALID_ROMAN_ERROR_CODE;
    }
    return SUCCESS_CODE;
}

int getRuleFor(char roman) {
  char romanString[2] = {roman, '\0'};
  int i;
  for(i=0; i<6; i++) {
    if (strcmp(romanString, ROMAN_NUMERALS_SEQUENCE_RULE[i].key) == 0) {
      return ROMAN_NUMERALS_SEQUENCE_RULE[i].value;
    }
  }
  return SUCCESS_CODE;
}
