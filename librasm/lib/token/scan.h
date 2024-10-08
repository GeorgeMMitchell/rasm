#ifndef RASM_SCAN_H
#define RASM_SCAN_H

#include <librasm/lib/token.h>

#define RASM_SCAN_IS_SPACE(ch) ('\0' <= (ch) && (ch) <= ' ')

#define RASM_SCAN_IS_ALPHA(ch) \
	(('A' <= (ch) && (ch) <= 'Z') || ('a' <= (ch) && (ch) <= 'z'))

#define RASM_SCAN_IS_BINARY(ch) ('0' <= (ch) && (ch) <= '1')

#define RASM_SCAN_IS_OCTAL(ch) ('0' <= (ch) && (ch) <= '7')

#define RASM_SCAN_IS_DECIMAL(ch) ('0' <= (ch) && (ch) <= '9')

#define RASM_SCAN_IS_HEXADECIMAL(ch) \
	(('A' <= (ch) && (ch) <= 'F') || ('a' <= (ch) && (ch) <= 'f') || \
	  RASM_SOURCE_CHAR_IS_DECIMAL((ch)))

#define RASM_SCAN_IS_ALPHANUM(ch) \
	(RASM_SCAN_IS_DECIMAL((ch)) || RASM_SCAN_IS_ALPHA((ch)))

#define RASM_SCAN_CHAR(ch, source, error) \
	do { \
		if (source->buffer_cur < source->buffer_end) { \
			(ch) = *++source->buffer_cur; \
		} else { \
			int ec = rasm_source_fill_buffer(source, error); \
			if (ec == RASM_FAILURE) { (ch) = '\0'; } \
		} \
	} while (0)

int rasm_token_scan_string(
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

int rasm_token_scan_symbol(
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

int rasm_token_scan_number(
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

int rasm_token_scan_number_rational(
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

int rasm_token_scan_number_integer(
  struct rasm_token *, struct rasm_source *, struct rasm_error *);

#endif
