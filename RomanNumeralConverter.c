#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralConverter.h"
struct KeyValuePair {
     char *key;
     int value;
};

const struct KeyValuePair ROMAN_NUMERALS_SEQUENCE_RULE_MAP[6] = {{"I", 3}, {"X", 3}, {"C", 3}, {"V", 1}, {"L",1}, {"D", 1}};
const struct KeyValuePair BASIC_ROMAN_TO_NUMBER_MAP[7] = {{"I", 1}, {"V", 5}, {"X", 10}, {"L", 50}, {"C", 100}, {"D", 500}, {"M", 1000}};

int toNumeric(int * result, const char *roman) {
  *result = 1;
  int code = validateRomanNumeral(roman);
  if (code == INVALID_ROMAN_ERROR_CODE) {
    return INVALID_ROMAN_ERROR_CODE;
  }

  if (strlen(roman) > 1) {
    int candidateValue = getBasicRomanToNumberValue(roman[1]);
    int prefixCandidateValue = getBasicRomanToNumberValue(roman[0]);
    if (candidateValue > prefixCandidateValue)
      *result = candidateValue - prefixCandidateValue;
  } else {
    *result = getBasicRomanToNumberValue(roman[0]);
  }

  return SUCCESS_CODE;
}

int validateRomanNumeral(const char *roman) {
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
    if (strcmp(romanString, ROMAN_NUMERALS_SEQUENCE_RULE_MAP[i].key) == 0) {
      return ROMAN_NUMERALS_SEQUENCE_RULE_MAP[i].value;
    }
  }
  return SUCCESS_CODE;
}

int getBasicRomanToNumberValue(const char roman) {
  int i;
  char romanString[2] = {roman, '\0'};

  for(i=0; i<7; i++) {
    if (strcmp(romanString, BASIC_ROMAN_TO_NUMBER_MAP[i].key) == 0) {
      return BASIC_ROMAN_TO_NUMBER_MAP[i].value;
    }
  }
  return INVALID_ROMAN_ERROR_CODE;
}
