#ifndef RASM_ERROR_H
#define RASM_ERROR_H

#include <setjmp.h>

#include <librasm/lib/api.h>
#include <librasm/lib/number.h>

#define RASM_SUCCESS 0

#define RASM_FAILURE 1

#define RASM_ERROR_MESSAGE_SIZE 128

struct rasm_error_file {
	const char *name;
	rasm_size line;
	rasm_size column;
};

struct rasm_error {
	jmp_buf assemble_call;
	struct rasm_error_file file;
	rasm_size message_size;
	char message[RASM_ERROR_MESSAGE_SIZE];
};

RASM_API void rasm_error_message(
  struct rasm_error *, const char * /* format */, ...);

#endif
