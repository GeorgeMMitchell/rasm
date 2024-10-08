#include <stdarg.h>
#include <string.h>

#include <librasm/lib/charconv.h>

#include <librasm/lib/debug.h>
#include <librasm/lib/error.h>

static void
error_write_string(struct rasm_string *message, struct rasm_string_view string)
{
	if (message->size + string.size < RASM_ERROR_MESSAGE_SIZE) {
		strncpy(
		  message->chars + message->size, string.chars, string.size);

		message->size += string.size;

	} else {
		strncpy(message->chars + message->size, string.chars,
		  RASM_ERROR_MESSAGE_SIZE - message->size - 4);

		message->size = RASM_ERROR_MESSAGE_SIZE;
	}
}

static void
error_write_size(struct rasm_string *message, rasm_size value)
{
	struct rasm_string size_buffer;

	size_buffer.chars = message->chars + message->size;

	size_buffer.size = RASM_ERROR_MESSAGE_SIZE - message->size;

	rasm_size_to_chars(size_buffer, value, RASM_BASE_10);

	message->size += strlen(size_buffer.chars);
}

static void
error_write_ssize(struct rasm_string *message, rasm_ssize value)
{
	struct rasm_string ssize_buffer;

	ssize_buffer.chars = message->chars + message->size;

	ssize_buffer.size = RASM_ERROR_MESSAGE_SIZE - message->size;

	rasm_ssize_to_chars(ssize_buffer, value, RASM_BASE_10);

	message->size += strlen(ssize_buffer.chars);
}

void
rasm_error_message(struct rasm_error *error, const char *format, ...)
{
	char ch;
	va_list argp;
	struct rasm_string message;

	RASM_DEBUG_ASSERT(error);
	RASM_DEBUG_ASSERT(format);

	va_start(argp, format);

	message.chars = error->message;
	message.size  = 0;

	for (ch = *format; ch != '\0'; ch = *++format) {
		if (ch == '\\') {
			ch = *++format;

			if (ch == '\0') { break; }

		} else if (ch == '%') {
			ch = *++format;

			if (ch == '\0') { break; }

			if (ch == 's') {
				struct rasm_string_view string;

				string.chars = va_arg(argp, const char *);
				string.size  = strlen(string.chars);

				error_write_string(&message, string);

			} else if (ch == 'd') {
				rasm_ssize i = va_arg(argp, rasm_ssize);

				error_write_ssize(&message, i);

			} else if (ch == 'u') {
				rasm_size u = va_arg(argp, rasm_size);

				error_write_size(&message, u);
			}
		}

		if (RASM_ERROR_MESSAGE_SIZE <= message.size) {
			memcpy(error->message + RASM_ERROR_MESSAGE_SIZE - 4,
			  "...", 4);

			break;
		}

		message.chars[message.size++] = ch;
	}

	va_end(argp);

	error->message_size = message.size;
}
