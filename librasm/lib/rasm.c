#include <librasm/rasm.h>

#include <librasm/lib/charconv.h>
#include <librasm/lib/syntax.h>

#include <librasm/lib/debug.h>

int
rasm_assemble(struct rasm_input *input, struct rasm_context *ctx)
{
	int srci;

	RASM_DEBUG_ASSERT(input);
	RASM_DEBUG_ASSERT(ctx);

	if (!input->srcv || !input->srcc) {
		rasm_error_message(&ctx->error, "no input source files");

		return RASM_FAILURE;
	}

	if (setjmp(ctx->error.assemble_call) == RASM_FAILURE) {
		if (ctx->source.file) { rasm_source_close(&ctx->source); }

		return RASM_FAILURE;
	}

	for (srci = 0; srci < input->srcc; ++srci) {
		rasm_source_open(input->srcv[srci], &ctx->source, &ctx->error);

		for (;;) {
			rasm_token_scan(RASM_TOKEN_SYMBOL, &ctx->token,
			  &ctx->source, &ctx->error);

			if (ctx->token.type == RASM_TOKEN_EOF) { break; }

			// RASM_DEBUG_TOKEN_PRINT((ctx->token));
		}

		rasm_source_close(&ctx->source);
	}

	return RASM_SUCCESS;
}
