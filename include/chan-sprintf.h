#include "chan-sprintf/c_sprintf-impl.h"

static inline int c_vsprintf(char* str, const char *format, va_list ap);
static inline int c_sprintf(char* str, const char *format, ...);

