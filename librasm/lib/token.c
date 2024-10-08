#include <string.h>

#include <librasm/lib/source.h>
#include <librasm/lib/token.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

#include <librasm/lib/token/scan.h>

int
rasm_token_scan(enum rasm_token_type expected, struct rasm_token *token,
  struct rasm_source *source, struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(token);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	for (;;) {
		char ch;

		if (source->buffer_end <= source->buffer_cur) {
			int ec = rasm_source_fill_buffer(source, error);

			if (ec == RASM_FAILURE) {
				token->type = RASM_TOKEN_EOF;

				return RASM_SUCCESS;
			}
		}

		ch = *source->buffer_cur;

		if (!RASM_SCAN_IS_SPACE(ch)) { break; }

		if (RASM_SOURCE_IS_NEWLINE(source->buffer_cur)) {
			++source->line;

			source->buffer_cur += RASM_SOURCE_NEWLINE_LENGTH;

		} else {
			++source->buffer_cur;
		}
	}

	switch (expected) {
		case RASM_TOKEN_SYMBOL:
			return rasm_token_scan_symbol(token, source, error);

		case RASM_TOKEN_STRING:
			return rasm_token_scan_string(token, source, error);

		case RASM_TOKEN_NUMBER_INTEGER:
			return rasm_token_scan_number_integer(
			  token, source, error);

		case RASM_TOKEN_NUMBER_RATIONAL:
			return rasm_token_scan_number_rational(
			  token, source, error);

		case RASM_TOKEN_EOF:
			if (source->eof) {
				token->type = RASM_TOKEN_EOF;

				return RASM_SUCCESS;

			} else {
				error->file.name = source->filename;
				error->file.line = source->line;

				rasm_error_message(
				  error, "end of file expected");

				longjmp(error->assemble_call, RASM_FAILURE);
			}

		case RASM_TOKEN_ANY:
			return RASM_FAILURE;
	}

	return RASM_FAILURE;
}
