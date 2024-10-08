#ifndef RASM_CHARCONV_H
#define RASM_CHARCONV_H

#include <librasm/lib/string.h>

struct rasm_float_chars {
	struct rasm_string_view mantissa_whole;
	struct rasm_string_view mantissa_fraction;
	struct rasm_string_view exponent;
	rasm_sign mantissa_sign;
	rasm_sign exponent_sign;
};

RASM_API int rasm_size_from_chars(
  rasm_size *, struct rasm_string_view, rasm_base);

RASM_API int rasm_ssize_from_chars(
  rasm_ssize *, struct rasm_string_view, rasm_base, rasm_sign);

RASM_API int rasm_size_to_chars(struct rasm_string, rasm_size, rasm_base);

RASM_API int rasm_ssize_to_chars(struct rasm_string, rasm_ssize, rasm_base);

RASM_API int rasm_float16_to_chars(struct rasm_string, rasm_float, rasm_base);

#endif
