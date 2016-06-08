#pragma once
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "chan-sprintf/c_num_conv-impl.h"


static inline int c_vsprintf(char* str, const char *format, va_list ap);
static inline int c_sprintf(char* str, const char *format, ...)
	    __attribute__((format(printf, 2, 3)));

#define PADDING(p_str, field_width, char_padding, len)	while (--(field_width) > (len)) *(p_str)++ = char_padding;

#define NUMBER_TYPE(qualifier, num, flags, args)  switch(qualifier){\
	case 'l':\
			 num = (flags & SIGN)?(signed long long)va_arg(args, signed long) :va_arg(args, unsigned long);\
	break;\
	case 'q':\
			 num = (flags & SIGN)?va_arg(args, signed long long) :va_arg(args, unsigned long long);\
	break;\
	case 'Z':\
			 num = va_arg(args, size_t);\
	break;\
	case 'h':\
			 num = (flags & SIGN) ? (signed long long) (signed short) va_arg(args, int): (unsigned short)va_arg(args, int);\
	break;\
	default:\
			num = (flags & SIGN) ? (signed long long)va_arg(args, int): va_arg(args, unsigned int);\
}\


#define NUMBER_CONV(str, num, base, qualifier,flags, args, field_width, precision) \
            NUMBER_TYPE(qualifier, num, flags, args);\
{\
	if (flags & LEFT) flags &= ~ZEROPAD;\
	char c = (flags & ZEROPAD) ? '0' : ' ';\
	char* p_str = str;\
    const char* special ="";\
    if (flags & SPECIAL){\
        special = (base == 16)?  (flags & LARGE)? "X0" :  "x0": "0";\
    }\
	str = number_c(str, num, base, precision, flags, special, !(flags & LEFT)?field_width:0, c);\
	len = str - p_str -1; \
	if ((flags & LEFT)) PADDING(p_out, field_width, ' ', len);   \
}


static inline int skip_vsprintf( const char *format, va_list ap){
	int count = 0;
	char *p_in = (char*)format;
	bool printed = false;
	int flags;		/* flags to number_c() */
	int base;
	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
						   number_c of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */
	int number_tmp;
	unsigned long long num;
	char* str_tmp;
	int len;
	while(1){
        while(*p_in != 0 && *p_in != '%' ){
            ++p_in;
            ++count;
        }

        if(*p_in == 0){
            break;
        }
	
        flags = 0;
		field_width = -1;
		precision = -1;
		qualifier = -1;
		base = 10;
		++p_in;
		printed = false;
		while(!printed){ 
			switch(*p_in){
				// Flags, field width and precision
				case '-': 
					flags |= LEFT;
					p_in++;
					break;
				case '+': flags |= PLUS;
					p_in++;
						  break;
				case ' ': flags |= SPACE;
					p_in++;
						  break;
				case '#': flags |= SPECIAL;
						  ++p_in; 
						  break;
				case '.':
						  precision = 0;
						  ++p_in; 
						  break;
				case '0': 
						  if(!( flags  || (precision != -1))){
							  flags |= ZEROPAD; 
							  break;
						  }
				case '1': case '2': case '3': case '4': case '5': case '6': case '7':  case '8': case '9':
						  number_tmp = skip_atoi_c((const char**)&p_in);
						  if(precision == 0){
							  precision = number_tmp;	
						  }else {
							  field_width = number_tmp;	
						  }

						  break;
				case '*':
						  /* it's the next argument */
						  number_tmp = va_arg(ap, int);
						  if(precision == 0){
							  precision = (number_tmp > 0 )? precision: 0;	
						  }else {
							  if(number_tmp < 0){
								  flags |= LEFT;
								  number_tmp = -number_tmp;
							  }
							  field_width = number_tmp;	
						  }
						  break;
				case 'l':
						  if (*p_in == 'l' && *(p_in + 1) == 'l') {
							  qualifier = 'q';
							  p_in += 2;
							  break;
						  }
				case 'h': case 'L': case 'Z':
						  qualifier = *p_in++;
						  break;

						  // Numbers
				case 'd':case 'i':
						  flags |= SIGN;
                          NUMBER_TYPE(qualifier, num, flags, ap);
                          number_tmp =  count_digits(num, base, precision,  flags);
                          count += (number_tmp > field_width)? number_tmp:  field_width;

						  ++p_in;
						  printed = true;
						  break;
				case 'c':
						  count += (field_width > 0)? field_width: 1;
						  ++p_in; 
						  printed = true;
						  break;
				case 'o': 
						  base = 8;
						  //NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	
				case'u': 
						  //NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	
				case 'x': 
						  base = 16;
						  //NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	

				case 'X':
						  flags |= LARGE;
						  //NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;


				case 'p':
						  if (field_width == -1) {
							  field_width = 2*sizeof(void *);
							  flags |= ZEROPAD;
						  }
						 // p_out = number_c(p_out,
						 //   	  (unsigned long) va_arg(ap, void *), 16,
						 //   	  field_width, precision, flags, 0, 0);
						  ++p_in; 
						  printed = true;
						  break;

						  // String
				case 's':
						  str_tmp = va_arg(ap, char *);
						  if (!str_tmp){	
							  str_tmp = (char*) "(null)";
						  }
						  len = strnlen(str_tmp, precision);
                          count += (len > field_width)? len : field_width;
						  ++p_in; 
						  printed = true;
						  break;
				case 'n':
						  ++p_in; 
						  printed = true;
						  break;
				case 'g': case 'G':
				case 'f': case 'F':
                        //TODO: add default precision to all double
                          //p_out = dtoa(va_arg(ap, double), p_out, precision, false);
						  ++p_in;
						  printed = true;
						  break;
				case 'e': case 'E':
						  //p_out = dtoa(va_arg(ap, double), p_out, precision, true );
						  ++p_in;
						  printed = true;
						  break;
				case 'a': case 'A':
				case '%':
				default:
						  ++p_in;
                          ++count;
						  printed = true;
						  break;
			}
		}
	}
	return count;
}
static inline int skip_sprintf( const char *format, ...){
	va_list va;
	va_start(va, format);
    int rc = skip_vsprintf(format,va);
	va_end(va);
	return rc;

}

static inline int c_vsprintf(char* str, const char *format, va_list ap){
	char *p_out = str;
	char *p_in = (char*)format;
	bool printed = false;
	int flags;		/* flags to number_c() */
	int base;
	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
						   number_c of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */
	int number_tmp;
	unsigned long long num;
	char* str_tmp;
	int len;
	*p_out = 0;
	while(1){
        while(*p_in != 0 && *p_in != '%' ){
            *p_out++ = *p_in++;
        }
        if(*p_in == 0){
            break;
        }
		flags = 0;
		field_width = -1;
		precision = -1;
		qualifier = -1;
		base = 10;
		++p_in;
		printed = false;
		while(!printed){ 
			switch(*p_in){
				// Flags, field width and precision
				case '-': 
					flags |= LEFT;
					p_in++;
					break;
				case '+': flags |= PLUS;
					p_in++;
						  break;
				case ' ': flags |= SPACE;
					p_in++;
						  break;
				case '#': flags |= SPECIAL;
						  ++p_in; 
						  break;
				case '.':
						  precision = 0;
						  ++p_in; 
						  break;
				case '0': 
						  if(!( flags  || (precision != -1))){
							  flags |= ZEROPAD; 
							  break;
						  }
				case '1': case '2': case '3': case '4': case '5': case '6': case '7':  case '8': case '9':
						  number_tmp = skip_atoi_c((const char**)&p_in);
						  if(precision == 0){
							  precision = number_tmp;	
						  }else {
							  field_width = number_tmp;	
						  }

						  break;
				case '*':
						  /* it's the next argument */
						  number_tmp = va_arg(ap, int);
						  if(precision == 0){
							  precision = (number_tmp > 0 )? precision: 0;	
						  }else {
							  if(number_tmp < 0){
								  flags |= LEFT;
								  number_tmp = -number_tmp;
							  }
							  field_width = number_tmp;	
						  }
						  break;
				case 'l':
						  if (*p_in == 'l' && *(p_in + 1) == 'l') {
							  qualifier = 'q';
							  p_in += 2;
							  break;
						  }
				case 'h': case 'L': case 'Z':
						  qualifier = *p_in++;
						  break;

						  // Numbers
				case 'd':case 'i':
						  flags |= SIGN;
						  NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision);
						  ++p_in;
						  printed = true;
						  break;
				case 'c':
						  if (!(flags & LEFT)) PADDING(p_out, field_width, ' ', 0);
						  *p_out++ = (char) va_arg(ap, int);
						  PADDING(p_out, field_width, ' ', 0);
						  ++p_in; 
						  printed = true;
						  break;
				case 'o': 
						  base = 8;
						  NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	
				case'u': 
						  NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	
				case 'x': 
						  base = 16;
						  NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;	

				case 'X':
						  flags |= LARGE;
						  NUMBER_CONV(p_out, num, base,qualifier,flags, ap, field_width, precision); 
						  ++p_in; 
						  printed = true;
						  break;


				case 'p':
						  if (field_width == -1) {
							  field_width = 2*sizeof(void *);
							  flags |= ZEROPAD;
						  }
						  p_out = number_c(p_out,
								  (unsigned long) va_arg(ap, void *), 16,
								   precision, flags, "", 0, 0);
						  ++p_in; 
						  printed = true;
						  break;

						  // String
				case 's':
						  str_tmp = va_arg(ap, char *);
						  if (!str_tmp){	
							  str_tmp = (char*) "(null)";
						  }
						  len = strnlen(str_tmp, precision);
						  if (!(flags & LEFT)) PADDING(p_out, field_width, ' ', len - 1);
                          memcpy(p_out, str_tmp, len);
                          p_out += len;
						  PADDING(p_out, field_width, ' ', len - 1);
						  ++p_in; 
						  printed = true;
						  break;
				case 'n':
						  if (qualifier == 'l') {
							  long * ip = va_arg(ap, long *);
							  *ip = (str - p_out);
						  } else if (qualifier == 'Z') {
							  size_t * ip = va_arg(ap, size_t *);
							  *ip = (str - p_out);
						  } else {
							  int * ip = va_arg(ap, int *);
							  *ip = (str - p_out);
						  }
						  ++p_in; 
						  printed = true;
						  break;
				case 'g': case 'G':
				case 'f': case 'F':
                        //TODO: add default precision to all double
                          p_out = dtoa(va_arg(ap, double), p_out, precision, false);
						  ++p_in;
						  printed = true;
						  break;
				case 'e': case 'E':
						  p_out = dtoa(va_arg(ap, double), p_out, precision, true );
						  ++p_in;
						  printed = true;
						  break;
				case 'a': case 'A':
				case '%':
				default:
						  *p_out++ = *p_in++;
						  printed = true;
						  break;
			}
		}
	}
	*p_out = 0;
	return p_out - str;
}

static inline int c_sprintf(char* str, const char *format, ...){
	va_list va;
	va_start(va, format);
    int rc = c_vsprintf(str,format,va);
	va_end(va);
	return rc;

}

