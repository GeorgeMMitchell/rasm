#ifndef RASM_STRING_H
#define RASM_STRING_H

#include <librasm/lib/api.h>
#include <librasm/lib/number.h>

#define STRING_MAX_SIZE 256

#ifdef RASM_DEBUG
#define RASM_DEBUG_ASSERT_STRING(str) \
	do { \
		RASM_DEBUG_ASSERT(str); \
		RASM_DEBUG_ASSERT(str->chars); \
	} while (0)
#else
#define RASM_DEBUG_ASSERT_STRING(str) ((void)0)
#endif

struct rasm_string_view {
	const char *chars;
	rasm_size size;
};

struct rasm_string {
	char *chars;
	rasm_size size;
};

struct rasm_error;

RASM_API void rasm_string_alloc(
  struct rasm_string_view, struct rasm_string *, struct rasm_error *);

RASM_API void rasm_string_concat(
  struct rasm_string_view, struct rasm_string *, struct rasm_error *);

RASM_API void rasm_string_dealloc(struct rasm_string *);

#endif
