#pragma once
#include <stdint.h>
#include <stdio.h>


#include <math.h>
#include <string.h>
// For printf
#include <stdio.h>



static inline char * c_round_str(char *s, char ** p, double n){
	char * p_p = *p;
	char * result = p_p - 1;
	
	bool overload = (n > 0 && *p_p == '9') || ( n > 0 && *p_p == '0')? true: false;
	int increment = (n > 0 && *p_p > '5') ? 
			overload? -9 : 1
		: (n > 0 && *p_p < '6')? 
			overload ? 9 : -1
		: 0;
	while(increment){
		--p_p;
		if( *p_p == '.') --p_p;
		*(p_p) += increment;
		increment = 0;
		if(overload){
			overload = (n > 0 && *p_p == '9') || ( n > 0 && *p_p == '0')? true: false;
			increment = (n > 0 && *p_p > '5') ? 
					overload? -9 : 1
				: (n > 0 && *p_p < '6')? 
					overload ? 9 : -1
				: 0;
		}
	}

	return result;

}

/**
   * Double to ASCII
    */
static inline char * dtoa(double n,char *s,  int precision_with) {
    double PRECISION = pow(10, -(precision_with+1));
    char* p_dot = NULL;
	char *c = s;
	// handle special cases
	if (isnan(n)) {
		*s++ = 'n';
		*s++ = 'a';
		*s++ = 'n';
		return s;
	} else if (isinf(n)) {
		if(n < 0){
			*s++ = '-';
		}
		*s++ = 'i';
		*s++ = 'n';
		*s++ = 'f';
		return s;
//		strcpy(s, "inf");
	} else if (n == 0.0) {
		*s++ = '0';
		return s;
	} else {
		int digit, m, m1 = 0;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp) {
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);
			m1 = m;
			m = 0;
		}
		if (m < 1.0) {
			m = 0;
		}
		// convert the number
		while (n > PRECISION || m >= 0) {
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0){
				*(c++) = '.';
                p_dot = c;   
            }
			m--;
		}
		
//		printf("*C= %c\n", *(c-1));
//		c_round_str(s, &c,n );
        int pre = precision_with - (c - p_dot);
        printf("n= %d\n", pre);
	    while(pre--> 0){
			*(c++) = '0';
        }
        
        if (useExp) {
			// convert the exponent
			int i, j;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			} else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m-1; i<j; i++, j--) {
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}else{
			*c++ = 'e';
			*c++ = '+';
			*c++ = '0';
			*c++ = '0';
		}
		

		*(c) = '\0';
        printf("result= %s\n", s );
	}
	return c;
}



static inline char* itoa(unsigned long long value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr_reverse = result, tmp_char;
	unsigned long long tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - ((unsigned long long)(value * base)))];
	} while ( value );

	// Apply negative sign
	if (((signed long long)tmp_value) < 0) *ptr++ = '-';
	char * end = ptr;
	*ptr-- = '\0';
	while(ptr_reverse < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr_reverse;
		*ptr_reverse++ = tmp_char;
	}
	return end;
}



static inline int skip_atoi_c(const char **s)
{
	int i, c;
	const char * p_str = *s;
	
	for (i = 0; '0' <= (c = *p_str) && c <= '9'; ++p_str)
		i = i*10 + c - '0';
	
	*s = p_str;
	return i;
}

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define LARGE	64		/* use 'ABCDEF' instead of 'abcdef' */

#define do_div_c(n, base) ({						\
		unsigned int __base = (base);					\
		unsigned int __rem;						\
		__rem = ((unsigned long long)(n)) % __base;			\
		(n) = ((unsigned long long)(n)) / __base;			\
		__rem;								\
		})


static inline char * number_c(char * str, unsigned long long num, int base, int precision, int type, char sign, int left_pad, char left_pad_char)
{
	const char *digits = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
	int i;
	char* ptr = str, *ptr_reverse = str, tmp_char;
	unsigned long long tmp_value, tmp_num = num;
//	const char * special = "x0";

	if (base < 2 || base > 36)
		return 0;

	if (type & LARGE)
		digits = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


	if ((type & SIGN) && (((signed long long)num) < 0ll) )  {
		tmp_num = -num;
		sign = '-';	
	}else{
		tmp_num = num;
	}
	
	do {
		tmp_value = tmp_num;
		tmp_num /= base;
		*ptr++ = digits [35 + (tmp_value - ((unsigned long long)(tmp_num * base)))];
	} while ( tmp_num );
	//NUMBER al reves
	i = (ptr - ptr_reverse);	
	// Fill precision with zeros	
	while (i < precision--)
		*ptr++ = '0';

	// Add SIGN
	if (sign) {
			*ptr++  = sign;
	}

//	while(*special){
//		*ptr++ = *special++;
//	}	
		
//	// Add special prefix
//	if (type & SPECIAL){
//		if (base==8)
//			*ptr++ = '0';
//		else if (base==16) {
////			*ptr++ = digits[33];
//			*ptr++ = 'x';
//			*ptr++ = '0';
//		}
//	}
//
//
	left_pad -= (ptr - ptr_reverse);
	
	while (left_pad-- > 0)
			*ptr++ = left_pad_char;
	// Do reverse
	char * end = ptr;
//	*ptr-- = '\0';
	--ptr;
	while(ptr_reverse < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr_reverse;
		*ptr_reverse++ = tmp_char;
	}

//	ptr = end;
	// Add right spaces
//	while (right_pad-- > 0)
//		*ptr++ = ' ';
	
	return end;
}



