#include <stdio.h>
#include <string.h>

#include <librasm/lib/charconv.h>
#include <librasm/lib/charconv/base.h>
#include <librasm/lib/charconv/table.h>
#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

int
rasm_ssize_from_chars(rasm_ssize *r_value, struct rasm_string_view string,
  rasm_base base, rasm_sign sign)
{
	rasm_ssize nvalue, digit, nmult, nsum;
	rasm_size idx;

	RASM_DEBUG_ASSERT(string.size);

	idx    = string.size - 2;
	nmult  = -1;
	nvalue = -1 * RASM_CHARCONV_DIGIT_FROM_CHAR(string.chars[idx]);

	do {
		--idx;

		digit = RASM_CHARCONV_DIGIT_FROM_CHAR(string.chars[idx]);

		if ((nmult < -1) && (RASM_SSIZE_MIN / nmult <= base)) {
			return RASM_FAILURE;
		}

		nmult *= base;

		if ((nmult < -1) && (RASM_SSIZE_MIN / nmult <= digit)) {
			return RASM_FAILURE;
		}

		nsum = digit * nmult;

		if (nvalue <= RASM_SSIZE_MIN - nsum) { return RASM_FAILURE; }

		nvalue += nsum;

	} while (idx);

	if (sign == RASM_POSITIVE) {
		if (RASM_SSIZE_MIN == nvalue) { return RASM_FAILURE; }

		nvalue *= -1;
	}

	*r_value = nvalue;

	return RASM_SUCCESS;
}

int
rasm_ssize_to_chars(
  struct rasm_string string, rasm_ssize value, rasm_base base)
{
	struct charconv_base_traits base_traits;

	rasm_uint8 leading_1;
	rasm_uint8 chars_needed;
	rasm_uint8 digit;
	rasm_sign value_sign;

	RASM_DEBUG_ASSERT(string.chars && string.size);

	switch (base) {
		case RASM_BASE_10:
			if (sprintf(string.chars, RASM_SSIZE_FMT, value) < 0) {
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

	if (value < 0) {
		*string.chars = '-';
		++string.chars;
		--string.size;

		if (RASM_SSIZE_MIN < value) {
			value *= -1;

		} else {
			return rasm_size_to_chars(string, value, base);
		}
	}

	if ((rasm_size)value < (rasm_uint)base) {
		chars_needed = 1 + base_traits.prefix_length;

		if (string.size < chars_needed) { return RASM_FAILURE; }

		strncpy(
		  string.chars, base_traits.prefix, base_traits.prefix_length);

		string.chars[base_traits.prefix_length] =
		  RASM_CHARCONV_DIGIT_FROM_CHAR(value);

		return RASM_SUCCESS;
	}

	leading_1 = sizeof(rasm_ssize) * CHAR_BIT - 1;

	do {
		--leading_1;

		rasm_size leading_1_mask = (rasm_size)1 << leading_1;

		if (value & leading_1_mask) { break; }

	} while (leading_1);

	if (!leading_1 && value_sign == RASM_NEGATIVE) {}

	chars_needed = ((leading_1 / base_traits.bits_per_digit) + 1) +
		       base_traits.prefix_length;

	if (string.size <= chars_needed) { return RASM_FAILURE; }

	while (base_traits.prefix_length <= --chars_needed) {
		digit = value & base_traits.digit_mask;

		string.chars[chars_needed] =
		  RASM_CHARCONV_DIGIT_FROM_CHAR(digit);

		value >>= base_traits.bits_per_digit;
	}

	strncpy(string.chars, base_traits.prefix, base_traits.prefix_length);

	return RASM_SUCCESS;
}
