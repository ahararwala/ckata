#include<stdio.h>
#include <check.h>
#include "RomanNumeralCalculator.h"
#include "RomanNumeralConverter.h"

static void assertAddRomanNumerals(char *inputRoman1, char *inputRoman2, char *expectedRoman){
  char actual[16] = "";
  int exitCode = addRomanNumerals(actual, inputRoman1, inputRoman2);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_str_eq(expectedRoman, actual);
}
static void assertAddRomanNumeralsInvalid(char *inputRoman1, char *inputRoman2, int expectedError){
  char actual[16] = "";
  int exitCode = addRomanNumerals(actual, inputRoman1, inputRoman2);
  ck_assert_int_eq(exitCode, INVALID_ROMAN_ERROR_CODE);
}
static void assertSubtractRomanNumerals(char *inputRoman1, char *inputRoman2, char *expectedRoman){
  char actual[16] = "";
  int exitCode = subtractRomanNumerals(actual, inputRoman1, inputRoman2);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_str_eq(expectedRoman, actual);
}
static void assertSubtractRomanNumeralsInvalid(char *inputRoman1, char *inputRoman2, int expectedError){
  char actual[16] = "";
  int exitCode = subtractRomanNumerals(actual, inputRoman1, inputRoman2);
  ck_assert_int_eq(exitCode, INVALID_ROMAN_ERROR_CODE);
}


START_TEST(addTests) {
  assertAddRomanNumerals("I","I","II");
  assertAddRomanNumerals("II","I","III");
  assertAddRomanNumerals("V","V","X");
  assertAddRomanNumerals("X","I","XI");
  //Kata test cases
  assertAddRomanNumerals("XIV","LX","LXXIV");
  assertAddRomanNumerals("II","II","IV");
  assertAddRomanNumerals("D","D","M");
  assertAddRomanNumerals("MMX","XVI","MMXXVI");
}
END_TEST
START_TEST(addValidationTests) {
  assertAddRomanNumeralsInvalid("IIII","I",INVALID_ROMAN_ERROR_CODE);
  assertAddRomanNumeralsInvalid("I","IIII",INVALID_ROMAN_ERROR_CODE);
}
END_TEST

START_TEST(addValidationTests_sumExceeding3999){
       assertAddRomanNumeralsInvalid("MMMCMXCVIII","II", INVALID_ROMAN_ERROR_CODE);
}
END_TEST


START_TEST(subtractTests) {
  assertSubtractRomanNumerals("III","I","II");
  assertSubtractRomanNumerals("VI","V","I");
  assertSubtractRomanNumerals("X","I","IX");
  assertSubtractRomanNumerals("LX","XIV","XLVI");
  assertSubtractRomanNumerals("CM","DM","CD");
}
END_TEST

START_TEST(subtractValidationTests_resultZeroOrNegative){
       assertSubtractRomanNumeralsInvalid("II","II", INVALID_ROMAN_ERROR_CODE);
       assertSubtractRomanNumeralsInvalid("III","IV", INVALID_ROMAN_ERROR_CODE);
}
END_TEST

Suite* romanNumeralCalculatorSuite(void) {
    Suite *romanCalculatorSuite = suite_create("RomanNumeralCalculatorSuite");

    TCase *addTestCase = tcase_create("Addition of Roman Numeral");
    TCase *subtractTestCase = tcase_create("Subtraction of Romal Numeral");
    suite_add_tcase(romanCalculatorSuite, subtractTestCase);
    suite_add_tcase(romanCalculatorSuite, addTestCase);

    tcase_add_test(addTestCase, addTests);
    tcase_add_test(addTestCase, addValidationTests);
    tcase_add_test(addTestCase, addValidationTests_sumExceeding3999);

    tcase_add_test(subtractTestCase, subtractTests);
    tcase_add_test(subtractTestCase, subtractValidationTests_resultZeroOrNegative);

    return romanCalculatorSuite;
}
