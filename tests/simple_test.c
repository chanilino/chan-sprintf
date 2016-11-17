#include <stdio.h>
#include <sys/time.h>

#include "chan-sprintf.h"
#include "chan-sprintf/chan-cache-sprintf.h"

#define diff_timeval_us(t2, t1) (((t2).tv_sec - (t1).tv_sec) * 1000000l )+ ((t2).tv_usec - (t1).tv_usec)
void swap_1(char * str){
    char *c = str;
    int i, j;
    int m = strlen(str) ;
	for (i = 0, j = m-1; i<j; i++, j--) {
			// swap without temporary
			c[i] ^= c[j];
			c[j] ^= c[i];
			c[i] ^= c[j];
	}
    
}

void swap_2(char * str){
	char tmp_char;
    int m = strlen(str) -1;
    char *ptr = str + m;
    char * ptr_reverse = str;
    while(ptr_reverse < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr_reverse;
		*ptr_reverse++ = tmp_char;
	}


}

void swap_3(char * str){
    int m = strlen(str) -1;
    char *ptr = str + m;
    char * ptr_reverse = str;
    while(ptr_reverse < ptr) {
        *ptr_reverse ^= *ptr;
        *ptr ^= *ptr_reverse;
        *ptr_reverse++ ^= *ptr--;
	}
    
}

int main(void){
	char msg[512];
	char number[128];
	int i;
    int n;
	double prec = 0.00001;
	struct timeval time_begin, time_end;
	const int number_of_values = 2000000;
	double value[number_of_values];


    char  string_test [512];
    cache_sprintf c1 = {0};	
    cache_sprintf c2 = {0};	
    cache_sprintf c3 = {0};	
    cache_sprintf c4 = {0};	
    cache_sprintf c5 = {0};	
    cache_sprintf c6 = {0};	

    c_cache_literal *l;
    c_cache_integer *c_i;
    c_cache_string *c_s;

    l = calloc(1, sizeof(c_cache_literal));
    l->literal = "Hola ";
    l->len = strlen(l->literal);
    c1.process = proccess_cache_literal; 
    c1.data = l;
    c1.next = &c2;

    c_i = calloc(1, sizeof(c_cache_integer));
    c_i->base =10;
    c_i->precision = -1;
	c_i->field_width = -1;
	c_i->qualifier = -1;
    c2.process = proccess_cache_integer; 
    c2.data = c_i;
    c2.next = &c3;
    
    l = calloc(1, sizeof(c_cache_literal));
    l->literal = " otra vez: ";
    l->len = strlen(l->literal);
    c3.process = proccess_cache_literal; 
    c3.data = l;
    c3.next = &c4;

    c_s = calloc(1,sizeof(c_cache_string));
    c_s->precision = -1;
	c_s->field_width = -1;
    c4.process = proccess_cache_string; 
    c4.data = c_s;
    c4.next = &c5;
    
    
    l = calloc(1, sizeof(c_cache_literal));
    l->literal = ": ";
    l->len = strlen(l->literal);
    c5.process = proccess_cache_literal; 
    c5.data = l;
    c5.next = &c6;
    
    c6.process = proccess_cache_integer; 
    c_i = calloc(1, sizeof(c_cache_integer));
    c_i->base =10;
    c_i->precision = -1;
	c_i->field_width = -1;
	c_i->qualifier = -1;
    c6.data = c_i;
    
    

    struct timezone tz; 
    gettimeofday(&time_begin, &tz);
	for(i = 0; i < number_of_values; i++){
        n = c_sprintf( string_test, "Hola %d otra vez: %s: %d", 34, "Ahí va este string", 3243289);
	}
	gettimeofday(&time_end, NULL);
	printf("c_sprintf: %lu us. %d\n", diff_timeval_us(time_end, time_begin), n);
    printf("nocache:'%s'\n", string_test);
    
    
    gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
        n = _proccess_cache( string_test, &c1 , 34, "Ahí va este string", 3243289);
	}
	gettimeofday(&time_end, NULL);
	printf("    cache: %lu us. %d\n", diff_timeval_us(time_end, time_begin), n);
    printf("cache:  '%s'\n", string_test);
    
    return 0;


    gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
        n = c_sprintf( string_test, "Hola %d otra vez: %s: %d", 34, "Ahí va este string", 3243289);
	}
	gettimeofday(&time_end, NULL);
	printf("c_sprintf: %lu us. %d\n", diff_timeval_us(time_end, time_begin), n);
    return 0;
    
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
        n = snprintf(NULL,0, "Hola %d otra vez: %s: %d", 34, "Ahí va este string", 3243289);
	}
	gettimeofday(&time_end, NULL);
	printf("  sprintf: %lu us: %d\n", diff_timeval_us(time_end, time_begin), n);
    
    strcpy(string_test,  "hola este es mi mundo al reves mucho y muy guay");
    return 0; 
    strcpy(string_test,  "hola este es mi mundo al reves mucho y muy guay");
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
        swap_3(string_test);
	}
	gettimeofday(&time_end, NULL);
	printf("swap3: %lu us. '%s'\n", diff_timeval_us(time_end, time_begin), string_test);
   
    return 0;
    
    
    strcpy(string_test,  "hola este es mi mundo al reves mucho y muy guay");
    swap_2(string_test);
    printf("swap_2: '%s'\n", string_test);
    swap_2(string_test);
    printf("swap_2: '%s'\n", string_test);
    
    strcpy(string_test,  "hola este es mi mundo al reves mucho y muy guay");
    swap_3(string_test);
    printf("swap_3: '%s'\n", string_test);
    swap_3(string_test);
    printf("swap_3: '%s'\n", string_test);
    return 0; 







	// Init values;
	i = 0;
	value[i++] = 4.4232384298;
	value[i++] = 4.99999;
	for(; i < number_of_values; i++){
			value[i] = -(((value[i-1] *1.09 ) - 3.454 ));
	}
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			//dtoa(0.0, number, prec);
	}
	gettimeofday(&time_end, NULL);
	printf("     dtoa: %lu us\n", diff_timeval_us(time_end, time_begin));
	
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			sprintf(number,"%.5e", 0.0);
	}
	gettimeofday(&time_end, NULL);
	printf("  sprintf: %lu us\n", diff_timeval_us(time_end, time_begin));
	
	gettimeofday(&time_begin, NULL);
	for(i = 0; i < number_of_values; i++){
			skip_sprintf(number,"%.5e", 0.0);
	}
	gettimeofday(&time_end, NULL);
	printf("c_sprintf: %lu us\n", diff_timeval_us(time_end, time_begin));
    return 0;

	for(i = 1; i < number_of_values; i+=991){
			//dtoa(value[i], number, prec);
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
