#include<stdio.h>
#include <check.h>
#include "../src/RomanNumeralConverter.h"
#include "RomanNumeralCalculatorTest.h"

struct InputExpected {
    int numberInput;
    char *expectedRoman;
};
const struct InputExpected CHECK_ALL_REQUIRED_PAIRS[SIZE_OF_TO_ROMAN_CONVERSION_MAP] = {{1, "I"},{4, "IV"},{5, "V"},{9, "IX"},{10, "X"},{40, "XL"},{50, "L"},{90, "XC"},{100, "C"},{400, "CD"},{500, "D"},{900, "CM"},{1000, "M"}};

int result;

static void assertRomanIsInValid(char * input){
  int actualCode = toNumeric(&result, input);
  ck_assert_int_eq(actualCode, INVALID_ROMAN_ERROR_CODE);
}

static void assertRomanIsConvertedToNumeral(char *input, int expectedResult){
  int exitCode = toNumeric(&result, input);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_int_eq(result, expectedResult);
}

static void assertNumberIsConvertedToRoman(int input, char *expectedResult){
  char actual[16] = "";
  int exitCode = toRoman(actual, input);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_str_eq(actual, expectedResult);
}

START_TEST(toNumericValidationInvalidRomanSequenceTests) {
	assertRomanIsInValid("IIII");
	assertRomanIsInValid("XXXX");
	assertRomanIsInValid("CCCC");
	assertRomanIsInValid("VV");
	assertRomanIsInValid("LL");
	assertRomanIsInValid("DD");
	assertRomanIsInValid("Z");
	assertRomanIsInValid("JJ");
	assertRomanIsInValid("abc");
	assertRomanIsInValid("NULL");
	assertRomanIsInValid(NULL);
	assertRomanIsInValid("");
	assertRomanIsInValid("   ");
}
END_TEST

START_TEST(toNumericValidationInvalidSequenceMixedRomanTests) {
	assertRomanIsInValid("IIIXXIIII");
	assertRomanIsInValid("VXXXXDCC");
}
END_TEST
START_TEST(toNumericBasicConversionTests) {
	assertRomanIsConvertedToNumeral("I", 1);
  assertRomanIsConvertedToNumeral("V", 5);
  assertRomanIsConvertedToNumeral("X", 10);
  assertRomanIsConvertedToNumeral("L", 50);
  assertRomanIsConvertedToNumeral("C", 100);
  assertRomanIsConvertedToNumeral("D", 500);
  assertRomanIsConvertedToNumeral("M", 1000);
}
END_TEST

START_TEST(toNumericShouldDeductWhenLowerValueRomanIsBeforeHigherValueRomanTests) {
  assertRomanIsConvertedToNumeral("IV", 4);
  assertRomanIsConvertedToNumeral("IX", 9);
  assertRomanIsConvertedToNumeral("CM", 900);
}
END_TEST

START_TEST(toNumericShouldAddWhenLowerValueRomanIsAfterHigherValueRomanTests) {
  assertRomanIsConvertedToNumeral("VI", 6);
  assertRomanIsConvertedToNumeral("XI", 11);
  assertRomanIsConvertedToNumeral("LX", 60);
  assertRomanIsConvertedToNumeral("III", 3);
  assertRomanIsConvertedToNumeral("VII", 7);
  assertRomanIsConvertedToNumeral("MLXVI", 1066);
}
END_TEST

START_TEST(toNumericShouldAddOrSubtractDependingUponThePositionTests) {
  assertRomanIsConvertedToNumeral("CMXCIX", 999);
  assertRomanIsConvertedToNumeral("MMXVI", 2016);
  assertRomanIsConvertedToNumeral("LXXIV", 74);
  assertRomanIsConvertedToNumeral("MMMCMXCIX", 3999);
  assertRomanIsConvertedToNumeral("DCCVII", 707);
  assertRomanIsConvertedToNumeral("LXXXIX", 89);
  assertRomanIsConvertedToNumeral("MCMXCV", 1995);
}
END_TEST


START_TEST(toRomanSuffixTests) {
  assertNumberIsConvertedToRoman(1, "I");
  assertNumberIsConvertedToRoman(2, "II");
  assertNumberIsConvertedToRoman(3, "III");
  assertNumberIsConvertedToRoman(5, "V");
  assertNumberIsConvertedToRoman(6, "VI");
  assertNumberIsConvertedToRoman(8, "VIII");
}
END_TEST

START_TEST(toRomanPrefixTests) {
  assertNumberIsConvertedToRoman(4, "IV");
  assertNumberIsConvertedToRoman(9, "IX");
}
END_TEST

START_TEST(toRomanCheckAllRequiredValuesForAlgorithmTests) {
  int i;
  for (i = 0; i < SIZE_OF_TO_ROMAN_CONVERSION_MAP; i++) {
      assertNumberIsConvertedToRoman(CHECK_ALL_REQUIRED_PAIRS[i].numberInput, CHECK_ALL_REQUIRED_PAIRS[i].expectedRoman);
  }
}
END_TEST

int main(void)
{
    int nf;

    Suite *romanConverterSuite = suite_create("RomanNumeralConverterSuite");
    Suite *calculatorSuite = romanNumeralCalculatorSuite();

    TCase *toNumericTestCase = tcase_create("Convert Roman to Numeral");
    TCase *toRomanTestCase = tcase_create("Convert Numeral to Roman Numeral");

    SRunner *sr = srunner_create(romanConverterSuite);
    srunner_add_suite(sr, calculatorSuite);

    suite_add_tcase(romanConverterSuite, toRomanTestCase);
    suite_add_tcase(romanConverterSuite, toNumericTestCase);

    tcase_add_test(toNumericTestCase, toNumericValidationInvalidRomanSequenceTests);
    tcase_add_test(toNumericTestCase, toNumericValidationInvalidSequenceMixedRomanTests);
    tcase_add_test(toNumericTestCase, toNumericBasicConversionTests);
    tcase_add_test(toNumericTestCase, toNumericShouldDeductWhenLowerValueRomanIsBeforeHigherValueRomanTests);
    tcase_add_test(toNumericTestCase, toNumericShouldAddWhenLowerValueRomanIsAfterHigherValueRomanTests);
    tcase_add_test(toNumericTestCase, toNumericShouldAddOrSubtractDependingUponThePositionTests);

    tcase_add_test(toRomanTestCase, toRomanSuffixTests);
    tcase_add_test(toRomanTestCase, toRomanPrefixTests);
    tcase_add_test(toRomanTestCase, toRomanCheckAllRequiredValuesForAlgorithmTests);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
