#ifndef RASM_CHARCONV_TABLE_H
#define RASM_CHARCONV_TABLE_H

#include <librasm/lib/number.h>

#define RASM_CHARCONV_DIGIT_FROM_CHAR(ch) (charconv_digit_table[ch - '0'])

#define RASM_CHARCONV_CHAR_FROM_DIGIT(d) (charconv_char_table[d])

extern const rasm_int8 charconv_digit_table[66];

extern const char charconv_char_table[36];

#endif
