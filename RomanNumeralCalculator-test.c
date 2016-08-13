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

START_TEST(addTests) {
  assertAddRomanNumerals("I","I","II");
  assertAddRomanNumerals("II","I","III");
}
END_TEST

Suite* romanNumeralCalculatorSuite(void) {
    Suite *romanCalculatorSuite = suite_create("RomanNumeralCalculatorSuite");

    TCase *addTestCase = tcase_create("Convert Roman to Numeral");
    TCase *subtractTestCase = tcase_create("Convert Numeral to Roman Numeral");

    suite_add_tcase(romanCalculatorSuite, addTestCase);
    tcase_add_test(addTestCase, addTests);
    return romanCalculatorSuite;
}
