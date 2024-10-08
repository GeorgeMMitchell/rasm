#ifndef RASM_FLOAT_H
#define RASM_FLOAT_H

#include <librasm/lib/number.h>

struct rasm_float_components {
	rasm_ssize mantissa;
	rasm_uint exponent;
	rasm_sign sign;
};

#endif
