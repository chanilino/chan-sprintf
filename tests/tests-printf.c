#include <stdlib.h>
#include <check.h>

#include "tests-printf.h"




int main(void){
	int number_failed;
    SRunner *sr;

	Suite* sb = suite_bench_printf();
	Suite* sf = suite_functional_printf();
    sr = srunner_create(sf);
	srunner_add_suite(sr, sb);
    srunner_run_all(sr, CK_ENV);
    number_failed = srunner_ntests_failed(sr);
	end_suite_bench_printf();
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
