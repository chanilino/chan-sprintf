#pragma once

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
    }else if(flags & PLUS){ \
        special = "+";\
    }\
	str = number_c(str, num, base, precision, flags, special, !(flags & LEFT)?field_width:0, c);\
	int len = str - p_str -1; \
	if ((flags & LEFT)) PADDING(p_out, field_width, ' ', len);   \
}


