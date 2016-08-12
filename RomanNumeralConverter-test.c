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

START_TEST(toNumericValidationInvalidBasicRomanTests)
{
	assertRomanIsInValid("IIII");
	assertRomanIsInValid("XXXX");
	assertRomanIsInValid("CCCC");
	assertRomanIsInValid("VV");
	assertRomanIsInValid("LL");
	assertRomanIsInValid("DD");
}
END_TEST
START_TEST(toNumericBasicConversionTests)
{
	assertRomanIsConvertedToNumeral("I", 1);
}
END_TEST
int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, toNumericValidationInvalidBasicRomanTests);
    tcase_add_test(tc1_1, toNumericBasicConversionTests);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
