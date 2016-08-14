#ifndef ROMAN_NUMERAL_CONVERTER_H

#define INVALID_ROMAN_ERROR_CODE -1
#define SUCCESS_CODE 0
#define SIZE_OF_TO_ROMAN_CONVERSION_MAP 13
#define SIZE_OF_BASIC_ROMAN_TO_NUMBER_MAP 7
#define SIZE_OF_ROMAN_NUMERALS_SEQUENCE_RULE_MAP 6

int toNumeric(int * result, const char* romanInput);
int toRoman(char* result, int numberInput);

#endif
