#include <stdlib.h>
#include <check.h>
#include <printf.h>
#include <string.h>
#include <limits.h>
#include "c_printf.h"
#include "tests-printf.h"

#define compare_print_func(f1, str_sprintf, n_sprintf ,f2, str_csprintf, n_csprintf ,fmt, ...) \
	str_sprintf[0] = 0; str_csprintf[0] = 0;\
	n_sprintf = f1(str_sprintf, fmt, __VA_ARGS__);\
	n_csprintf = f2(str_csprintf, fmt, __VA_ARGS__);\
	ck_assert_str_eq(str_sprintf, str_csprintf);\
	ck_assert_int_eq(n_sprintf, n_csprintf);


START_TEST(test_integer)
{
	char str_sprintf[512];
	char str_csprintf[512];
	int n_sprintf, n_csprintf;
    //INTEGERS
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %d", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%d:%d:%d", 7, 4, 0);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MAX %d", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MIN %d", INT_MIN);
    // %i
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %i", 3534555);

    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5d'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5d'", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5d'", INT_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5d'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5d'", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5d'", INT_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5d'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5d'", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5d'", INT_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5d'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5d'", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5d'", INT_MIN);
    
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5d'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5d'", INT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5d'", INT_MIN);
	
    // Unsigned integers
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %u", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%u:%u:%u", 7, 4, 0);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MAX %u", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MIN %u", 0);

    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5u'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5u'", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5u'", 0);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5u'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5u'", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5u'", 0);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5u'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5u'", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5u'", 0);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5u'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5u'", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5u'", 0);
    
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5u'", 7);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5u'", UINT_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5u'", 0);
}
END_TEST

START_TEST(test_long)
{
	char str_sprintf[512];
	char str_csprintf[512];
	int n_sprintf, n_csprintf;
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %ld", 3534535547l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%ld:%ld:%ld", 7l, 34543245324l, 0l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%ld", -5435432542l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MAX %ld", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MIN %ld", LONG_MIN);
	// %i
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %li", 3534535547l);
    
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5ld'", 72342l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5ld'", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5ld'", LONG_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5ld'", 742343l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5ld'", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5ld'", LONG_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5ld'", 754354l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5ld'", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5ld'", LONG_MIN);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5ld'", 7343l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5ld'", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5ld'", LONG_MIN);
    
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5ld'", 754354l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5ld'", LONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5ld'", LONG_MIN);
	
    // Unsigned integers
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %lu", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%lu:%lu:%lu", 7l, 4l, 0l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MAX %lu", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "MIN %lu", 0l);

    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5lu'", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5lu'", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%5lu'", 0l);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5lu'", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5lu'", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "padding '%-5lu'", 0l);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5lu'", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5lu'", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%.5lu'", 0l);
	
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5lu'", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5lu'", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%3.5lu'", 0l);
    
    compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5lu'", 7l);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5lu'", ULONG_MAX);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "precision '%-3.5lu'", 0l);
}
END_TEST

typedef struct{
	double input_value;
	const char * expected_string;
	int expected_return;
}double_test_pair;

START_TEST(test_exp)
{
	char str_csprintf[512];
	int i, n_csprintf;
	double_test_pair tests_exp_numbers [] = {
		{3.5f, "3.5e+00", 7},
		{-3.5f, "-3.5e+00", 8},
		{3.5458730589043f, "3.54587e+00", 11},
		{-3.5458730589043f, "-3.54587e+00", 12},
		{0, "0", 1},
		{9999999999999999999999999999.99999999999f*9999999999999999.0f, "inf", 3},
		{-9999999999999999999999999999.99999999999f*9999999999999999.0f, "-inf", 4},
	};
	for(i = 0; i < sizeof(tests_exp_numbers)/sizeof(tests_exp_numbers[0]); i ++){
		n_csprintf = c_sprintf( str_csprintf, "%.5e", tests_exp_numbers[i].input_value);
		ck_assert_str_eq(tests_exp_numbers[i].expected_string, str_csprintf);
		ck_assert_msg(tests_exp_numbers[i].expected_return == n_csprintf,
				"expected len: %d != n_csprintf : %d in '%s'", 
				tests_exp_numbers[i].expected_return, n_csprintf,
				tests_exp_numbers[i].expected_string
				);

	}
}
END_TEST

START_TEST(test_string)
{
	char str_sprintf[512];
	char str_csprintf[512];
	int n_sprintf, n_csprintf;
    const char * NULL_STR = NULL;
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "%s:%s:%s", "Mi Mundo", "es", "asin");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Nothing '%s'","" );
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "NULL '%s'", NULL_STR);
}
END_TEST

START_TEST(test_mix)
{
	char str_sprintf[512];
	char str_csprintf[512];
	int n_sprintf, n_csprintf;
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %s", "Mundo");
}
END_TEST

START_TEST(test_padding)
{
	char str_sprintf[512];
	char str_csprintf[512];
	int n_sprintf, n_csprintf;
	//compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-5d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %08d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %8d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-8d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %018d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %18d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-18d", 34);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %02d", 343432);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-2d", 34423342);
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %9s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-9s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %2s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-2s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %12s", "Mundo");
	compare_print_func(sprintf,str_sprintf, n_sprintf, c_sprintf,str_csprintf, n_csprintf, "Hola %-12s", "Mundo");
}
END_TEST

Suite* suite_functional_printf(void) {
	Suite *s;
		
	s = suite_create("Functional printf");

	TCase* tc_integer = tcase_create("Test integer");
	tcase_add_test(tc_integer, test_integer);
	suite_add_tcase(s, tc_integer);
	
	TCase* tc_long = tcase_create("Test long");
	tcase_add_test(tc_long, test_long);
	suite_add_tcase(s, tc_long);
	
	TCase* tc_exp = tcase_create("Test exp");
	tcase_add_test(tc_exp, test_exp);
	suite_add_tcase(s, tc_exp);
	
	TCase* tc_string = tcase_create("Test string");
	tcase_add_test(tc_string, test_string);
	suite_add_tcase(s, tc_string);
	
	TCase* tc_mix = tcase_create("Test mix");
	tcase_add_test(tc_mix, test_mix);
	suite_add_tcase(s, tc_mix);
	
	TCase* tc_pad = tcase_create("Test padding");
	tcase_add_test(tc_pad, test_padding);
	suite_add_tcase(s, tc_pad);
	
	return s;

}

