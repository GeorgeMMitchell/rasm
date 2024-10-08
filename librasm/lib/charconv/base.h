#ifndef RASM_CHARCONV_BASE_H
#define RASM_CHARCONV_BASE_H

#include <librasm/lib/number.h>

struct charconv_base_traits {
	const char *prefix;
	rasm_uint8 prefix_length;
	rasm_uint8 bits_per_digit;
	rasm_uint8 digit_mask;
};

extern const struct charconv_base_traits charconv_base_2;

extern const struct charconv_base_traits charconv_base_8;

extern const struct charconv_base_traits charconv_base_16;

#endif
