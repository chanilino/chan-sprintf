#include <stdio.h>
#include <sys/time.h>

#include "c_printf.h"
#define diff_timeval_us(t2, t1) (((t2).tv_sec - (t1).tv_sec) * 1000000l )+ ((t2).tv_usec - (t1).tv_usec)


int main(void){
	char msg[512];
	char number[128];
	int i;
	double prec = 0.00001;
	struct timeval time_begin, time_end;
	const int number_of_values = 10000;
	double value[number_of_values];
	// Init values;
	i = 0;
	value[i++] = 4.4232384298;
	value[i++] = 4.99999;
	for(; i < number_of_values; i++){
			value[i] = -(((value[i-1] *1.09 ) - 3.454 ));
	}
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			dtoa(value[i], number, prec);
	}
	gettimeofday(&time_end, NULL);
	printf("     dtoa: %lu us\n", diff_timeval_us(time_end, time_begin));
	
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			sprintf(number,"%.5e", value[i]);
	}
	gettimeofday(&time_end, NULL);
	printf("  sprintf: %lu us\n", diff_timeval_us(time_end, time_begin));
	
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			c_sprintf(number,"%.5e", value[i]);
	}
	gettimeofday(&time_end, NULL);
	printf("c_sprintf: %lu us\n", diff_timeval_us(time_end, time_begin));
	
	for(i = 1; i < number_of_values; i+=991){
			dtoa(value[i], number, prec);
			printf("     dtoa: %s\n", number);
			printf("sprintf e: %.5e\n", value[i]);
			c_sprintf(number,"c_print e: %.5e\n", value[i]);
			printf("%s\n", number);
//			printf("sprintf f: %.5f\n", value[i]);
	}
	return 0;
//	sprintf("msg: %d\n",a );
	c_sprintf(msg, "c: hola '%9s'\n", "Mundo");
	puts(msg);
	sprintf(msg, "s: hola '%9s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "c: hola '%-9s'\n", "Mundo");
	puts(msg);
	sprintf(msg, "s: hola '%-9s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "hola '%-9s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "hola '%12s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "hola '%2s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "hola '%-2s'\n", "Mundo");
	puts(msg);
	c_sprintf(msg, "-c_sprintf: hola '%-7d'\n", 23);
	puts(msg);
	sprintf(msg,   "  -sprintf: hola '%-7d'\n", 23);
	puts(msg);
	
	c_sprintf(msg, "c_sprintf: hola '%7d'\n", 23);
	puts(msg);
	sprintf(msg,   "  sprintf: hola '%7d'\n", 23);
	puts(msg);
//	
	return 0;
}
