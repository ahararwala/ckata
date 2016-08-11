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

START_TEST(toNumericValidationTests)
{
	assertRomanIsInValid("IIII");
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, toNumericValidationTests);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
