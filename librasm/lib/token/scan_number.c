#include <librasm/lib/source.h>
#include <librasm/lib/token.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

#include <librasm/lib/token/scan.h>

int
rasm_token_scan_number(struct rasm_token *token, struct rasm_source *source,
  struct rasm_error *error)
{
	struct rasm_string string;
	char ch;

	RASM_DEBUG_ASSERT(token);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	string.chars = source->buffer_cur;

	ch = *string.chars;

	if (ch == '-') {
		token->value.integer.is_signed = RASM_TRUE;

		RASM_SCAN_CHAR(ch, source, error);

		if (!ch) {
			error->file.name = source->filename;
			error->file.line = source->line;
			error->file.column =
			  RASM_SOURCE_CURRENT_COLUMN(source);

			rasm_error_message(error,
			  "end of file encountered while evaluating integer");

			longjmp(error->assemble_call, RASM_FAILURE);
		}
	}

	if (ch == '0') {
		RASM_SCAN_CHAR(ch, source, error);

		if (!ch || ch != '.' || ch != 'x' || ch != 'b' ||
		    !RASM_SCAN_IS_DECIMAL(ch)) {}
	}

	return RASM_SUCCESS;
}

int
rasm_token_scan_number_integer(struct rasm_token *token,
  struct rasm_source *source, struct rasm_error *error)
{
	struct rasm_string string;
	rasm_base base;
	char ch;

	RASM_DEBUG_ASSERT(token);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	token->type = RASM_TOKEN_NUMBER_INTEGER;

	string.chars = source->buffer_cur;

	ch = *string.chars;

	if (ch == '-') {
		token->value.integer.is_signed = RASM_FALSE;

		RASM_SCAN_CHAR(ch, source, error);

		if (!ch) {
			error->file.name = source->filename;
			error->file.line = source->line;
			error->file.column =
			  RASM_SOURCE_CURRENT_COLUMN(source);

			rasm_error_message(error,
			  "end of file encountered while evaluating integral");
		}

	} else {
	}

	if (ch == '0') {
		RASM_SCAN_CHAR(ch, source, error);

		if (ch == 'x') {
			token->value.integer.base = RASM_BASE_16;

		} else if (ch == 'b') {
			token->value.integer.base = RASM_BASE_2;

		} else if (RASM_SCAN_IS_OCTAL(ch)) {
			token->value.integer.base = RASM_BASE_8;

		} else {
			token->value.integer.value.u = 0;
			token->value.integer.base    = RASM_BASE_10;
			return RASM_SUCCESS;
		}
	}

	return RASM_SUCCESS;
}

int
rasm_token_scan_number_rational(struct rasm_token *token,
  struct rasm_source *source, struct rasm_error *error)
{
	return RASM_SUCCESS;
}
