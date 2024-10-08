#ifndef RASM_TOKEN_H
#define RASM_TOKEN_H

#include <librasm/lib/string.h>

struct rasm_token_integer {
	union {
		rasm_ssize i;
		rasm_size u;

	} value;

	rasm_base base;
	rasm_bool is_signed;
};

struct rasm_token_rational {
	union {
		rasm_size rational_max;
		rasm_uint64 rational_64;
		rasm_uint32 rational_32;
		rasm_uint16 rational_16;

	} value;

	rasm_base base;
};

enum rasm_token_type {
	RASM_TOKEN_EOF,
	RASM_TOKEN_NUMBER,
	RASM_TOKEN_NUMBER_INTEGER,
	RASM_TOKEN_NUMBER_RATIONAL,
	RASM_TOKEN_STRING,
	RASM_TOKEN_SYMBOL,
	RASM_TOKEN_ANY
};

union rasm_token_value {
	struct rasm_token_integer integer;
	struct rasm_token_rational rational;
	struct rasm_string string;
	struct rasm_string symbol;
};

struct rasm_token {
	union rasm_token_value value;
	enum rasm_token_type type;
	rasm_size line;
	rasm_size column;
};

struct rasm_source;
struct rasm_error;

RASM_API int rasm_token_scan(enum rasm_token_type /* expected */,
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

#endif
