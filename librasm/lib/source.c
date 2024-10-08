#include <stdio.h>
#include <string.h>

#include <librasm/lib/source.h>
#include <librasm/lib/string.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

void
rasm_source_open(
  const char *filename, struct rasm_source *source, struct rasm_error *error)
{
	long fpos;

	RASM_DEBUG_ASSERT(filename);
	RASM_DEBUG_ASSERT(source);
	RASM_DEBUG_ASSERT(error);

	source->file = (void *)fopen(filename, "rb");

	if (!source->file) {
		error->file.name = filename;

		rasm_error_message(error, "cannot open file");

		longjmp(error->assemble_call, RASM_FAILURE);
	}

	if (fseek((FILE *)source->file, 0, SEEK_END)) {
		error->file.name = filename;

		rasm_error_message(error, "fseek failure");

		longjmp(error->assemble_call, RASM_FAILURE);
	}

	fpos = ftell((FILE *)source->file);

	if (fpos < 0) {
		error->file.name = filename;

		rasm_error_message(error, "ftell failure");

		longjmp(error->assemble_call, RASM_FAILURE);
	}

	source->size = (rasm_size)fpos;

	if (source->size == 0) {
		error->file.name = filename;

		rasm_error_message(error, "empty file");

		longjmp(error->assemble_call, RASM_FAILURE);
	}

	rewind((FILE *)source->file);

	source->filename = filename;
	source->line	 = 1;

	rasm_source_fill_buffer(source, error);
}

void
rasm_source_close(struct rasm_source *source)
{
	RASM_DEBUG_ASSERT_SOURCE(source);

	fclose((FILE *)source->file);

	memset(source, 0, sizeof *source);
}

int
rasm_source_fill_buffer(struct rasm_source *source, struct rasm_error *error)
{
	rasm_size len;
	char *fgets_ret;

	RASM_DEBUG_ASSERT_SOURCE(source);
	RASM_DEBUG_ASSERT(error);

	if (source->size <= source->bytes_read) { return RASM_FAILURE; }

	if (source->eol) {
		++source->line;
		source->buffer_end_column = 0;
	}

	fgets_ret =
	  fgets(source->buffer, RASM_SOURCE_BUFFER_SIZE, (FILE *)source->file);

	if (!fgets_ret) {
		error->file.name = source->filename;
		error->file.line = source->line;

		rasm_error_message(error, "fgets failure");

		longjmp(error->assemble_call, errno);
	}

	len = strlen(source->buffer);

	source->buffer_end_column += len;

	source->buffer_cur  = source->buffer;
	source->bytes_read += len;
	source->buffer_end  = source->buffer + len;

	source->eol = RASM_SOURCE_IS_NEWLINE(
	  source->buffer_end - RASM_SOURCE_NEWLINE_LENGTH);

	source->eof = source->size <= source->bytes_read;

	return RASM_SUCCESS;
}
