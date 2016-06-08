#pragma once
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "chan-sprintf/c_string-util.h"

typedef enum{
    C_CACHE_LITERAL,
    C_CACHE_STRING,
    C_CACHE_INTEGER,
    C_CACHE_FLOAT,
}c_cache_sprint_type;

typedef struct{
    const char* literal;
    int len;
}c_cache_literal;

typedef struct{
    int precision;
    int flags;
    int field_width;
}c_cache_string;

typedef struct{
    char qualifier;
    int flags;
    int base;
    int precision;
    bool left_pad;
    int field_width;
}c_cache_integer;

typedef struct{
    char qualifier;
    int flags;
    int precision;
    bool left_pad;
    int field_width;
}c_cache_float;

typedef struct _cache_sprintf{
    c_cache_sprint_type type;
    struct _cache_sprintf* next;
    union{
        c_cache_literal m_literal;
        c_cache_string m_string;
        c_cache_integer m_integer;
        c_cache_float m_float;
    };
}cache_sprintf;


void create_cache( const char * fmt, ...){
    
}

static inline int proccess_cache_literal(char* p_str, c_cache_literal* cache){
    memcpy(p_str, cache->literal, cache->len);
    return cache->len;
}

static inline int proccess_cache_string(char* p_str, c_cache_string* cache, va_list ap){
    char *str = p_str;
    int len;
    char *str_tmp = NULL;
    str_tmp = va_arg(ap, char *);
    if (!str_tmp){	
        str_tmp = (char*) "(null)";
    }
    len = strnlen(str_tmp, cache->precision);
    if (!(cache->flags & LEFT)) PADDING(p_str, cache->field_width, ' ', len - 1);
    memcpy(p_str, str_tmp, len);
    p_str += len;
    PADDING(p_str, cache->field_width, ' ', len - 1);
    return p_str - str; 
}

static inline int proccess_cache_integer(char* p_str, c_cache_integer* cache, va_list ap){
    unsigned long long num;
    char * p_out = p_str;
    NUMBER_CONV(p_out, num, cache->base, cache->qualifier,cache->flags, ap, cache->field_width, cache->precision);
    return p_out - p_str;
}

static inline int proccess_cache_float(char* p_str, c_cache_integer* cache, va_list ap){
    return 0;
}

int proccess_cache(char* str, cache_sprintf* cache, va_list ap){
    char *p_str= str;

    while(cache){
        switch(cache->type){
            case C_CACHE_LITERAL:
                p_str += proccess_cache_literal(p_str, &cache->m_literal);
                break;
            case C_CACHE_STRING:
                p_str += proccess_cache_string(p_str, &cache->m_string, ap);
                break;
            case C_CACHE_INTEGER:
                p_str += proccess_cache_integer(p_str, &cache->m_integer, ap);
                break;
            case C_CACHE_FLOAT:
                p_str += proccess_cache_float(p_str, &cache->m_integer, ap);
            default:
                ;
                //Not implemented
        }
        cache = cache->next;
    }

    *p_str = 0;
    return p_str -str;
}

int _proccess_cache(char * str, cache_sprintf* cache, ...){
	va_list va;
    int rc;
	va_start(va, cache);
    rc = proccess_cache(str, cache,  va);
	va_end(va);
    return rc;


}

