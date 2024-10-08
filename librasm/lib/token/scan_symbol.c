#include <librasm/lib/source.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

#include <librasm/lib/token/scan.h>


int
rasm_token_scan_symbol(struct rasm_token *token, struct rasm_source *source,
  struct rasm_error *error)
{
	struct rasm_string symbol = {0};

	char ch;

	const char *symbol_begin;

	RASM_DEBUG_ASSERT(token);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	token->type = RASM_TOKEN_SYMBOL;

	symbol_begin = source->buffer_cur;

	struct rasm_string_view concat_string = {
	  symbol_begin, source->buffer_end - symbol_begin};

	for (;;) {
		if (source->buffer_end <= source->buffer_cur) {
			rasm_string_concat(concat_string, &symbol, error);

			rasm_source_fill_buffer(source, error);

			if (source->eof) {
				token->value.string.chars = symbol.chars;
				token->value.string.size  = symbol.size;
				token->line		  = source->line;

				return RASM_SUCCESS;
			}

			symbol_begin = source->buffer_cur;
		}

		ch = *source->buffer_cur;

		if (RASM_SCAN_IS_SPACE(ch)) {
			struct rasm_string_view concat_string = {
			  symbol_begin, source->buffer_cur - symbol_begin};

			rasm_string_concat(concat_string, &symbol, error);

			token->value.string.chars = symbol.chars;
			token->value.string.size  = symbol.size;
			token->line		  = source->line;

			return RASM_SUCCESS;
		}

		if (!RASM_SCAN_IS_ALPHANUM(ch) || ch != '_') {
			error->file.name = source->filename;
			error->file.line = source->line;

			rasm_error_message(error,
			  "invalid character encountered while scanning "
			  "symbol");

			longjmp(error->assemble_call, RASM_FAILURE);
		}

		++source->buffer_cur;
	}
}
