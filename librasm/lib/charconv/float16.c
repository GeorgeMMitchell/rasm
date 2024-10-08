#include <librasm/lib/charconv.h>
#include <librasm/lib/charconv/float.h>
#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

int
rasm_float16_to_chars(
  struct rasm_string string, rasm_float f16, rasm_base base)
{
	struct rasm_float_components cmp;

	RASM_DEBUG_ASSERT(string.chars && string.size);

	f16 &= 0xFFFF;

	cmp.sign     = f16 & 0x8000;
	cmp.exponent = f16 & 0x7C00;
	cmp.mantissa = f16 & 0x03FF;

	if (base == RASM_BASE_2) {}

	return RASM_SUCCESS;
}
