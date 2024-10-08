#ifndef RASM_H
#define RASM_H

#include <librasm/lib/version.h>
#include <librasm/lib/error.h>
#include <librasm/lib/input.h>
#include <librasm/lib/source.h>
#include <librasm/lib/token.h>

struct rasm_context {
	struct rasm_error error;
	struct rasm_source source;
	struct rasm_token token;
};

RASM_API int rasm_assemble(struct rasm_input *, struct rasm_context *);

#endif
