#include <stdio.h>
#include <string.h>

#include <librasm/lib/charconv.h>
#include <librasm/lib/charconv/base.h>
#include <librasm/lib/charconv/table.h>
#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

int
rasm_size_from_chars(
  rasm_size *r_value, struct rasm_string_view string, rasm_base base)
{
	rasm_size idx, value, digit, mult, sum;

	RASM_DEBUG_ASSERT(string.chars && string.size);

	idx   = string.size - 2;
	mult  = 1;
	value = (rasm_uint8)RASM_CHARCONV_DIGIT_FROM_CHAR(string.chars[idx]);

	do {
		--idx;

		digit =
		  (rasm_uint8)RASM_CHARCONV_DIGIT_FROM_CHAR(string.chars[idx]);

		if (RASM_SIZE_MAX / mult < (rasm_uint)base) {
			return RASM_FAILURE;
		}

		mult *= (rasm_uint)base;

		if (RASM_SIZE_MAX / mult < digit) { return RASM_FAILURE; }

		sum = digit * mult;

		if (RASM_SIZE_MAX - sum < value) { return RASM_FAILURE; }

		value += sum;

	} while (idx);

	*r_value = value;

	return RASM_SUCCESS;
}

int
rasm_size_to_chars(struct rasm_string string, rasm_size value, rasm_base base)
{
	struct charconv_base_traits base_traits;

	rasm_uint8 leading_1;
	rasm_uint8 chars_needed;
	rasm_uint8 digit;

	RASM_DEBUG_ASSERT(string.chars && string.size);

	switch (base) {
		case RASM_BASE_10:
			if (sprintf(string.chars, RASM_SIZE_FMT, value) < 0) {
				return RASM_FAILURE;
			}

			return RASM_SUCCESS;

		case RASM_BASE_2:
			base_traits = charconv_base_2;
			break;
		case RASM_BASE_8:
			base_traits = charconv_base_8;
			break;
		case RASM_BASE_16:
			base_traits = charconv_base_16;
			break;
	}

	if (value < (rasm_uint)base) {
		chars_needed = 1 + base_traits.prefix_length;

		if (string.size < chars_needed) { return RASM_FAILURE; }

		strncpy(
		  string.chars, base_traits.prefix, base_traits.prefix_length);

		string.chars[base_traits.prefix_length] =
		  RASM_CHARCONV_CHAR_FROM_DIGIT(value);

		return RASM_SUCCESS;
	}

	leading_1 = sizeof(rasm_size) * CHAR_BIT;

	while (leading_1--) {
		if (value & ((rasm_size)1 << leading_1)) { break; }
	}

	chars_needed = ((leading_1 / base_traits.bits_per_digit) + 1) +
		       base_traits.prefix_length;

	if (string.size <= chars_needed) { return RASM_FAILURE; }

	while (base_traits.prefix_length <= --chars_needed) {
		digit = value & base_traits.digit_mask;

		string.chars[chars_needed] =
		  RASM_CHARCONV_CHAR_FROM_DIGIT(digit);

		value >>= base_traits.bits_per_digit;
	}

	strncpy(string.chars, base_traits.prefix, base_traits.prefix_length);

	return RASM_SUCCESS;
}
