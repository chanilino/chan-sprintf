#include <stdlib.h>

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <printf.h>
#include <string.h>
#include "c_printf.h"
#include "assert.h"

#include "tests-printf.h"

#define diff_timeval_us(t2, t1) (((t2).tv_sec - (t1).tv_sec) * 1000000l )+ ((t2).tv_usec - (t1).tv_usec)
// Returns the number of chars printed
typedef int (*printf_func)(char*, const char*, ...);

// Returns the time in microseconds elapsed
typedef long (*test_func)(printf_func);

const char * f_summary_test = "/tmp/sumary_test.txt";

typedef struct{
	const char* id;
	test_func f;
	double speed_ratio;
}test_print_bench_info;

const int howmany = 10000000;

int print_itoa (FILE *stream,
		const struct printf_info *info,
		const void *const *args)
{
	char buffer[64];
	int n_tests;
	char *end;
	/* Format the output into a string. */
	const int input = *((int*)args[0]);
	/* Pad to the minimum field width and print to the stream. */
	end = itoa(input,buffer, 10);
	n_tests = end - buffer;
	fwrite(buffer, n_tests, 1, stream);

	/* Clean up and return. */
	return n_tests;
}

int print_itoa_arginfo (const struct printf_info *info, size_t n, int* argtypes, int * size)
{
	/* We always take exactly one argument and this is a pointer to the
	   structure.. */
	if (n == sizeof(int)){
		argtypes[0] = PA_INT;
		size[0] = sizeof(int);
	}
	// Number of parameters procesed
	return 1;
}




long test_long(printf_func f){
	char log[512];
	int i;
	long x;
	struct timeval time_begin, time_end;
	gettimeofday(&time_begin, NULL);
	x = time_begin.tv_usec;
	// Again to be more acurate
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		f(log, "One integer testing '%ld' happy...", x);
	}
	gettimeofday(&time_end, NULL);
	return diff_timeval_us(time_end, time_begin);
}


long test_exp(printf_func f){
	char log[512];
	int i;
	double x;
	struct timeval time_begin, time_end;
	srand((unsigned)time(NULL));
	x = (double)rand()*1.052371924322547795032f;
	x *= x;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		f(log, "testing '%e' happy...", x);
	}
	gettimeofday(&time_end, NULL);
	return diff_timeval_us(time_end, time_begin);
}

long test_integer(printf_func f){
	char log[512];
	int i;
	struct timeval time_begin, time_end;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		f(log, "One integer testing '%d' happy...", i);
	}
	gettimeofday(&time_end, NULL);
	
	return diff_timeval_us(time_end, time_begin);
}

long test_integers(printf_func f){
	char log[512];
	int i;
	struct timeval time_begin, time_end;
	struct timeval time;
	time_t t;
	struct tm * ptm;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		gettimeofday(&time, NULL);
		t = time.tv_sec;
   		ptm = gmtime (&t);
		f(log, "[%d-%d-%d %d:%d:%d.%d]: %d:\n", 
				1900 + ptm->tm_year, ptm->tm_mon+1,ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, 
				(int)(time.tv_usec/1000), i);
	}
	gettimeofday(&time_end, NULL);

	return diff_timeval_us(time_end, time_begin);
}

long test_msg_log(printf_func f){
	char log[512];
	int i;
	struct timeval time_begin, time_end;
	struct timeval time;
	time_t t;
	struct tm * ptm;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		gettimeofday(&time, NULL);
		t = time.tv_sec;
   		ptm = gmtime (&t);
		f(log, "[%d-%d-%d %d:%d:%d.%d]: %s%d: %s\n", 
				1900 + ptm->tm_year, ptm->tm_mon+1,ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, time.tv_usec/1000,
				"spdlog message #", i,"This is some text for your pleasure");
	}
	gettimeofday(&time_end, NULL);
	return diff_timeval_us(time_end, time_begin);

}

long test_string(printf_func f){
	char log[512];
	int i;
	struct timeval time_begin, time_end;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		f(log, "%s", "Very very happy");
	}
	gettimeofday(&time_end, NULL);
	return diff_timeval_us(time_end, time_begin);
}

long test_strings(printf_func f){
	char log[512];
	int i;
	struct timeval time_begin, time_end;
	gettimeofday(&time_begin, NULL);
	for (i = 0; i < howmany; ++i){
		f(log, "Today is %s %s of the %s log.", "The first", "day" "new");
	}
	gettimeofday(&time_end, NULL);
	return diff_timeval_us(time_end, time_begin);
}

test_print_bench_info* test_func_array;
static int n_tests = 0;

START_TEST(test_bench)
{
	int i;
	long t_sprintf;
	long t_csprintf;
    FILE * f = fopen(f_summary_test, "a");

    for (i = 0; i < n_tests; i++){
		t_sprintf = test_func_array[i].f(sprintf);
		t_csprintf = test_func_array[i].f(c_sprintf);
        fprintf(f, "| %-25s | %15ld | %15ld  | %15f |\n",
				test_func_array[i].id, t_csprintf, t_sprintf,
				(1.0f - (((double)t_csprintf)/((double)t_sprintf)))*100.0f);
		ck_assert_msg(t_sprintf > t_csprintf, "In '%s' is slower c_sprintf (%ld us) than sprintf (%ld us)", 
			test_func_array[i].id, t_csprintf, t_sprintf);
		//ck_assert_msg((t_sprintf * test_func_array[i].speed_ratio) > t_csprintf, 
		//		"In '%s' is slower than sprintf with ratio: %f. c_sprintf (%ld us); sprintf (%ld us)."
		//		" test ratio: %f; expected ratio: %f", 
		//		test_func_array[i].id, test_func_array[i].speed_ratio ,  t_csprintf, t_sprintf,
		//		((double)t_csprintf)/((double)t_sprintf), test_func_array[i].speed_ratio);
	}
    fclose(f);
}
END_TEST


void setup_integers(void)
{
	static test_print_bench_info test_func_array_integer [] = {
		{"test 1 integer", test_integer, 0.54},  
		{"test multiple integers", test_integers, 0.44},
	};
	test_func_array = test_func_array_integer;
	n_tests = sizeof(test_func_array_integer)/sizeof(test_func_array_integer[0]);
}

void setup_exp(void)
{
	static test_print_bench_info _test_func_array [] = {
		{"test exponential", test_exp, 0.82},
	};
	test_func_array = _test_func_array;
	n_tests = sizeof(_test_func_array)/sizeof(_test_func_array[0]);
}

void setup_longs(void)
{
	static test_print_bench_info _test_func_array [] = {
		{"test 1 long", test_long, 0.56},
	};
	test_func_array = _test_func_array;
	n_tests = sizeof(_test_func_array)/sizeof(_test_func_array[0]);
}

void setup_strings(void)
{
	static test_print_bench_info _test_func_array [] = {
		{"One string", test_string, 0.35},
		{"Multiple strings", test_string, 0.34},
	};
	test_func_array = _test_func_array;
	n_tests = sizeof(_test_func_array)/sizeof(_test_func_array[0]);
}

void setup_simple_log(void)
{
	static test_print_bench_info _test_func_array [] = {
		{"simple message log", test_msg_log, 0.48},
	};
	test_func_array = _test_func_array;
	n_tests = sizeof(_test_func_array)/sizeof(_test_func_array[0]);
}


void tear_down(void){
	test_func_array = NULL;
	n_tests = 0;
}

Suite* suite_bench_printf(void) {
	Suite *s;
		
	s = suite_create("Benchmark printf");

    FILE * f = fopen(f_summary_test, "w");
    fprintf(f, "| %-25s | %-15s | %-15s  | %-15s |\n", 
            "Test", "c_sprintf(us)", "sprintf(us)", "% faster" );
    fprintf(f, "|---------------------------+-----------------+------------------+-----------------|\n");
    fclose(f);
	/* Core test case */
	TCase* tc_integer = tcase_create("Test integer");
	tcase_add_checked_fixture(tc_integer, setup_integers, tear_down);
	tcase_add_test(tc_integer, test_bench);
	tcase_set_timeout(tc_integer,30);
	suite_add_tcase(s, tc_integer);
	
	TCase* tc_long = tcase_create("Test long");
	tcase_add_checked_fixture(tc_long, setup_longs, tear_down);
	tcase_add_test(tc_long, test_bench);
	tcase_set_timeout(tc_long,30);
	suite_add_tcase(s, tc_long);

	TCase* tc_exp = tcase_create("Test exponential");
	tcase_add_checked_fixture(tc_exp, setup_exp, tear_down);
	tcase_add_test(tc_exp, test_bench);
	tcase_set_timeout(tc_exp,30);
	suite_add_tcase(s, tc_exp);
	
	TCase* tc_string = tcase_create("Test string");
	tcase_add_checked_fixture(tc_string, setup_strings, tear_down);
	tcase_add_test(tc_string, test_bench);
	suite_add_tcase(s, tc_string);
	
	TCase* tc_simple_log = tcase_create("Test simple message log");
	tcase_add_checked_fixture(tc_simple_log, setup_simple_log, tear_down);
	tcase_add_test(tc_simple_log, test_bench);
	tcase_set_timeout(tc_simple_log,30);
	suite_add_tcase(s, tc_simple_log);

	return s;

}

void end_suite_bench_printf(void) {
}
