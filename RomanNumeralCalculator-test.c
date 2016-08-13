#include<stdio.h>
#include <check.h>
#include "RomanNumeralCalculator.h"

START_TEST(addTests) {
  ck_assert_int_eq(1, 1);
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
