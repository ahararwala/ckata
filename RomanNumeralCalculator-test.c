#include<stdio.h>
#include <check.h>
#include "RomanNumeralCalculator.h"
#include "RomanNumeralConverter.h"

static void assertAddRomanNumerals(char *inputRoman1, char *inputRoman2, char *expectedRoman){
  char actual[16] = "";
  int exitCode = addRomanNumerals(actual, inputRoman1, inputRoman2);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_str_eq(actual, expectedRoman);
}

static void assertAddRomanNumeralsInvalid(char *inputRoman1, char *inputRoman2, int expectedError){
  char actual[16] = "";
  int exitCode = addRomanNumerals(actual, inputRoman1, inputRoman2);
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

Suite* romanNumeralCalculatorSuite(void) {
    Suite *romanCalculatorSuite = suite_create("RomanNumeralCalculatorSuite");

    TCase *addTestCase = tcase_create("Convert Roman to Numeral");
    TCase *subtractTestCase = tcase_create("Convert Numeral to Roman Numeral");

    suite_add_tcase(romanCalculatorSuite, addTestCase);
    tcase_add_test(addTestCase, addTests);
    tcase_add_test(addTestCase, addValidationTests);
    tcase_add_test(addTestCase, addValidationTests_SumExceeding3999);
    return romanCalculatorSuite;
}
