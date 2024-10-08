#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <librasm/lib/string.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

void
rasm_string_alloc(struct rasm_string_view init, struct rasm_string *string,
  struct rasm_error *error)
{
	char *alloc;

	RASM_DEBUG_ASSERT(init.chars && init.size);
	RASM_DEBUG_ASSERT(string);
	RASM_DEBUG_ASSERT(error);

	alloc = (char *)malloc(init.size * sizeof(char));

	if (!alloc) {
		rasm_error_message(error,
		  "%s: rasm_string_alloc: call to malloc failed", __FILE__);

		longjmp(error->assemble_call, RASM_FAILURE);
	}

	strncpy(alloc, init.chars, init.size);

	string->chars = alloc;
	string->size  = init.size;

	alloc[init.size - 1] = '\0';
}

void
rasm_string_concat(struct rasm_string_view concat, struct rasm_string *string,
  struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(concat.chars && concat.size);
	RASM_DEBUG_ASSERT(string);
	RASM_DEBUG_ASSERT(error);

	if (string->chars) {
		char *alloc =
		  (char *)realloc(string->chars, string->size + concat.size);

		if (!alloc) {
			rasm_error_message(error,
			  "%s: rasm_string_concat: call to realloc failed",
			  __FILE__);

			longjmp(error->assemble_call, RASM_FAILURE);
		}

		strncpy(
		  string->chars + string->size - 1, concat.chars, concat.size);

		string->size += concat.size;

		string->chars[string->size - 1] = '\0';

	} else {
		rasm_string_alloc(concat, string, error);
	}
}

void
rasm_string_dealloc(struct rasm_string *string)
{
	RASM_DEBUG_ASSERT_STRING(string);

	free(string->chars);

	memset(string, 0, sizeof *string);
}
