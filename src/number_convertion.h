#pragma once
#include <stdint.h>
#include <stdio.h>


#include <math.h>
#include <string.h>
// For printf
#include <stdio.h>

static inline void mem_reverse(char * ptr, char* ptr_end){
    char tmp_char;
    while(ptr < ptr_end) {
		tmp_char = *ptr_end;
		*ptr_end--= *ptr;
		*ptr++ = tmp_char;
	}
}



/**
   * Double to ASCII
    */
static inline char * dtoa(double n,char *s,  int precision_with) {
//    double PRECISION = pow(10, -(precision_with+1));
    if(precision_with <= 0){
        precision_with =1;
    }
    char* p_tmp = NULL;
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
	} else if (n == 0.0) {
		*s++ = '0';
		*s++ = '.';
        while(precision_with--> 0){
               *s++ = '0';
        }
		*s++ = 'e';
		*s++ = '+';
		*s++ = '0';
		*s++ = '0';
		return s;
	} else {
		int digit, m, m1 = 0;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 1 || (neg && m >= 1) || m <= -1);
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
        while(precision_with > 0){
//		while (n > PRECISION || m >= 0) {
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
            if(p_tmp){
                precision_with--;
            }else if (m == 0 && n > 0){
				*(c++) = '.';
                p_tmp = c;   
            }
			m--;
		}
		
//        if (m > 0) {
        if (useExp) {
			// convert the exponent
//			int i, j;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			} else {
				*(c++) = '-';
				m1 = -m1;
			}
            p_tmp = c;   
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
            while( ( c -p_tmp ) < 2 ){
				*(c++) = '0';
                m++;
            }
            mem_reverse(c - m, c-1);
		}else{
			*c++ = 'e';
			*c++ = '+';
			*c++ = '0';
			*c++ = '0';
		}
		

		*(c) = '\0';
	}
	return c;
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


static inline char * number_c(char * str, unsigned long long num, int base, int precision, int type, char sign, int left_pad, char left_pad_char)
{
	const char *digits = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
	int i;
	char* ptr = str, *ptr_reverse = str;
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
    mem_reverse(ptr_reverse, ptr);

//	ptr = end;
	// Add right spaces
//	while (right_pad-- > 0)
//		*ptr++ = ' ';
	
	return end;
}



