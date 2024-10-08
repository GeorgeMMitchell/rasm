#ifndef RASM_SOURCE_H
#define RASM_SOURCE_H

#include <librasm/lib/api.h>
#include <librasm/lib/number.h>

#ifdef RASM_DEBUG
#define RASM_DEBUG_ASSERT_SOURCE(source_file) \
	do { \
		RASM_DEBUG_ASSERT((source_file)); \
		RASM_DEBUG_ASSERT((source_file)->file); \
	} while (0)
#else
#define RASM_DEBUG_ASSERT_SOURCE(source_file) ((void)0)
#endif

#ifdef _WIN32
#define RASM_SOURCE_NEWLINE	    ((const char *)"/r/n")
#define RASM_SOURCE_NEWLINE_LENGTH  2
#define RASM_SOURCE_IS_NEWLINE(str) (!strncmp((str), RASM_SOURCE_NEWLINE, 2))
#else
#define RASM_SOURCE_NEWLINE	    '\n'
#define RASM_SOURCE_NEWLINE_LENGTH  1
#define RASM_SOURCE_IS_NEWLINE(str) (*(str) == RASM_SOURCE_NEWLINE)
#endif

#define RASM_SOURCE_BUFFER_SIZE 128

#define RASM_SOURCE_CURRENT_COLUMN(source) \
	((source)->buffer_end_column - \
	  (rasm_size)((source)->buffer_end - (source)->buffer_cur))

struct rasm_source {
	void *file;
	const char *filename;
	rasm_size line;
	rasm_size size;
	rasm_size bytes_read;
	rasm_size buffer_end_column;
	rasm_bool eof;
	rasm_bool eol;
	char *buffer_cur;
	char *buffer_end;
	char buffer[RASM_SOURCE_BUFFER_SIZE];
};

struct rasm_error;

RASM_API void rasm_source_open(
  const char *, struct rasm_source *, struct rasm_error *);

RASM_API void rasm_source_close(struct rasm_source *);

RASM_API int rasm_source_fill_buffer(
  struct rasm_source *, struct rasm_error *);

#endif
