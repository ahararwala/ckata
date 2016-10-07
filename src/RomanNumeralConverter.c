#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "RomanNumeralConverter.h"

struct KeyValuePair {
     char *key;
     int value;
};

const struct KeyValuePair ROMAN_NUMERALS_SEQUENCE_RULE_MAP[SIZE_OF_ROMAN_NUMERALS_SEQUENCE_RULE_MAP] = {{"I", 3}, {"X", 3}, {"C", 3}, {"V", 1}, {"L",1}, {"D", 1}};
const struct KeyValuePair BASIC_ROMAN_TO_NUMBER_MAP[SIZE_OF_BASIC_ROMAN_TO_NUMBER_MAP] = {{"I", 1}, {"V", 5}, {"X", 10}, {"L", 50}, {"C", 100}, {"D", 500}, {"M", 1000}};
const struct KeyValuePair TO_ROMAN_CONVERSION_MAP[SIZE_OF_TO_ROMAN_CONVERSION_MAP] = {{"M",1000}, {"CM",900}, {"D",500}, {"CD",400}, {"C",100}, {"XC",90}, {"L",50}, {"XL",40}, { "X",10}, {"IX",9}, {"V",5}, {"IV",4}, {"I",1}};

static int appendRomanNumerals(int arabic, int value, char *romanPart, char *output) {
  int result = arabic;
  while (result >= value) {
    strcat(output, romanPart);
    result -= value;
  }
  return result;
}

static int getRuleFor(char roman) {
  char romanString[2] = {roman, '\0'};
  int i;
  for(i=0; i<SIZE_OF_ROMAN_NUMERALS_SEQUENCE_RULE_MAP; i++) {
    if (strcmp(romanString, ROMAN_NUMERALS_SEQUENCE_RULE_MAP[i].key) == 0) {
      return ROMAN_NUMERALS_SEQUENCE_RULE_MAP[i].value;
    }
  }
  return SUCCESS_CODE;
}

static int validate(int actualOccurances, char roman) {
    int allowedContiguousOccurrences = getRuleFor(roman);
    if (allowedContiguousOccurrences == SUCCESS_CODE) {
      return SUCCESS_CODE;
    }

    if (actualOccurances > allowedContiguousOccurrences) {
        return INVALID_ROMAN_ERROR_CODE;
    }
    return SUCCESS_CODE;
}

static int getBasicRomanToNumberValue(const char roman) {
  int i;
  char romanString[2] = {roman, '\0'};

  for(i=0; i<SIZE_OF_BASIC_ROMAN_TO_NUMBER_MAP; i++) {
    if (strcmp(romanString, BASIC_ROMAN_TO_NUMBER_MAP[i].key) == 0) {
      return BASIC_ROMAN_TO_NUMBER_MAP[i].value;
    }
  }
  return INVALID_ROMAN_ERROR_CODE;
}

static int validateRomanNumeral(const char *roman) {
  int trackContiguousOccurrences=0;
  int i = 0;
  char candidate = roman[i];
  while (roman[i] != '\0') {
      int code;
      code = getBasicRomanToNumberValue(roman[i]);
      if (code == INVALID_ROMAN_ERROR_CODE) { return code; }

      if (roman[i] == candidate) {
        trackContiguousOccurrences = trackContiguousOccurrences+1;
      } else {
        candidate = roman[i];
        trackContiguousOccurrences = 1;
      }
      code = validate(trackContiguousOccurrences, roman[i]);
      if (code == INVALID_ROMAN_ERROR_CODE) {
        return INVALID_ROMAN_ERROR_CODE;
      }
      i++;
  }
	return SUCCESS_CODE;
}

int toRoman(char *output, int arabic){
  int remaining = arabic;
  for (int i = 0; i < SIZE_OF_TO_ROMAN_CONVERSION_MAP; i++) {
     remaining = appendRomanNumerals(remaining, TO_ROMAN_CONVERSION_MAP[i].value, TO_ROMAN_CONVERSION_MAP[i].key, output);
  }
  return SUCCESS_CODE;
}

int toNumeric(int * result, const char *roman) {
  if (roman == NULL || strcmp(roman, "") == 0) { return INVALID_ROMAN_ERROR_CODE; }

  *result = 1;
  int code = validateRomanNumeral(roman);

  int i=strlen(roman)-1;
  char candidate = roman[i];
  int candidateValue = getBasicRomanToNumberValue(candidate);
  if (code == INVALID_ROMAN_ERROR_CODE) {
    return code;
  }
  int convertedValue = 0;
  for (int i= strlen(roman)-1; i >= 0; i--) {
      char current = roman[i];
      int currentRomanValue = getBasicRomanToNumberValue(current);
      if (candidateValue <= currentRomanValue)
          convertedValue = currentRomanValue + convertedValue;
      else
          convertedValue = convertedValue - currentRomanValue;

      candidateValue = currentRomanValue;
  }

  *result = convertedValue;
  return SUCCESS_CODE;
}
