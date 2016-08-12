#define INVALID_ROMAN_ERROR_CODE -1
#define SUCCESS_CODE 0

int toNumeric(int * result, const char* roman);
int validateRomanNumeral(const char* roman);
int validate(int actualOccurances, char roman);
int getRuleFor(char roman);
int getBasicRomanToNumberValue(const char *roman);
