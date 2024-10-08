#include <librasm/lib/source.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

#include <librasm/lib/token/scan.h>

int
rasm_token_scan_string(struct rasm_token *token, struct rasm_source *source,
  struct rasm_error *error)
{
	struct rasm_string string;
	const char *string_begin;

	RASM_DEBUG_ASSERT(token);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	string_begin = source->buffer_cur;

	for (;;) {
		if (source->buffer_end <= source->buffer_cur) {
			struct rasm_string_view concat_string = {
			  string_begin, source->buffer_end - string_begin};

			rasm_string_concat(concat_string, &string, error);

			rasm_source_fill_buffer(source, error);

			if (source->eof) {
				error->file.name = source->filename;
				error->file.line = source->line;
				rasm_error_message(error,
				  "end of file encountered while "
				  "evaluating string");

				longjmp(error->assemble_call, RASM_FAILURE);
			}

			string_begin = source->buffer_cur;
		}

		if (*source->buffer_cur == '"') {
			struct rasm_string_view concat_string = {
			  string_begin, source->buffer_cur - string_begin};

			rasm_string_concat(concat_string, &string, error);

			return RASM_SUCCESS;
		}

		++source->buffer_cur;
	}
}
