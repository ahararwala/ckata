#include<stdio.h>
#include <check.h>
#include "RomanNumeralConverter.h"

int result;

static void setup(){
    result = -100;
}
static void assertRomanIsInValid(char * input){
  int actualCode = toNumeric(&result, input);
  ck_assert_int_eq(actualCode, INVALID_ROMAN_ERROR_CODE);
}

static void assertRomanIsConvertedToNumeral(char *input, int expectedResult){
  int exitCode = toNumeric(&result, input);
  ck_assert_int_eq(exitCode, SUCCESS_CODE);
  ck_assert_int_eq(result, expectedResult);
}

START_TEST(toNumericValidationInvalidRomanSequenceTests)
{
	assertRomanIsInValid("IIII");
	assertRomanIsInValid("XXXX");
	assertRomanIsInValid("CCCC");
	assertRomanIsInValid("VV");
	assertRomanIsInValid("LL");
	assertRomanIsInValid("DD");
}
END_TEST

START_TEST(toNumericValidationInvalidSequenceMixedRomanTests)
{
	assertRomanIsInValid("IIIXXIIII");
	assertRomanIsInValid("VXXXXDCC");
}
END_TEST
START_TEST(toNumericBasicConversionTests)
{
	assertRomanIsConvertedToNumeral("I", 1);
  assertRomanIsConvertedToNumeral("V", 5);
  assertRomanIsConvertedToNumeral("X", 10);
  assertRomanIsConvertedToNumeral("L", 50);
  assertRomanIsConvertedToNumeral("C", 100);
  assertRomanIsConvertedToNumeral("D", 500);
  assertRomanIsConvertedToNumeral("M", 1000);
}
END_TEST

START_TEST(toNumericShouldDeductWhenLowerValueRomanIsBeforeHigherValueRomanTests)
{
  assertRomanIsConvertedToNumeral("IV", 4);
  assertRomanIsConvertedToNumeral("IX", 9);
  assertRomanIsConvertedToNumeral("CM", 900);
}
END_TEST

START_TEST(toNumericShouldAddWhenLowerValueRomanIsAfterHigherValueRomanTests)
{
  assertRomanIsConvertedToNumeral("VI", 6);
  assertRomanIsConvertedToNumeral("XI", 11);
  assertRomanIsConvertedToNumeral("LX", 60);
  assertRomanIsConvertedToNumeral("III", 3);
  assertRomanIsConvertedToNumeral("VII", 7);
  assertRomanIsConvertedToNumeral("MLXVI", 1066);
}
END_TEST
int main(void)
{
    Suite *s1 = suite_create("RomanNumeralConverterSuite");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, toNumericValidationInvalidRomanSequenceTests);
    tcase_add_test(tc1_1, toNumericValidationInvalidSequenceMixedRomanTests);
    tcase_add_test(tc1_1, toNumericBasicConversionTests);
    tcase_add_test(tc1_1, toNumericShouldDeductWhenLowerValueRomanIsBeforeHigherValueRomanTests);
    tcase_add_test(tc1_1, toNumericShouldAddWhenLowerValueRomanIsAfterHigherValueRomanTests);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
