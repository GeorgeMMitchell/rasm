#include <stdio.h>
#include <string.h>

#include <librasm/lib/charconv.h>
#include <librasm/lib/error.h>

#define RASM_TEST_CHARCONV_BUFFER_SIZE 16

int
main(void)
{
	static char char_buffer[RASM_TEST_CHARCONV_BUFFER_SIZE] = {0};

	struct rasm_string to_chars_buffer = {
	  char_buffer, RASM_TEST_CHARCONV_BUFFER_SIZE};

	int ec;
	rasm_size size_value;
	rasm_ssize ssize_value;

	struct rasm_string_view base10_string = {"72058", 6};
	struct rasm_string_view base16_string = {"ffFF", 5};
	struct rasm_string_view base2_string  = {"1010101", 8};

	puts("-- rasm_size_from_chars --");

	ec = rasm_size_from_chars(&size_value, base10_string, RASM_BASE_10);
	printf("input base-10 string: \"%s\"\n", base10_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SIZE_FMT "\n", size_value);

	ec = rasm_size_from_chars(&size_value, base16_string, RASM_BASE_16);
	printf("\ninput base-16 string: \"0x%s\"\n", base16_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SIZE_FMT "\n", size_value);

	ec = rasm_size_from_chars(&size_value, base2_string, RASM_BASE_2);
	printf("\ninput base-2 string: \"0b%s\"\n", base2_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SIZE_FMT "\n", size_value);

	puts("\n-- rasm_ssize_from_chars --");

	ec = rasm_ssize_from_chars(
	  &ssize_value, base10_string, RASM_BASE_10, RASM_NEGATIVE);
	printf("input base-10 string \"-%s\"\n", base10_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SSIZE_FMT "\n", ssize_value);

	ec = rasm_ssize_from_chars(
	  &ssize_value, base16_string, RASM_BASE_16, RASM_NEGATIVE);
	printf("input base-16 string \"-0x%s\"\n", base16_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SSIZE_FMT "\n", ssize_value);

	ec = rasm_ssize_from_chars(
	  &ssize_value, base2_string, RASM_BASE_2, RASM_NEGATIVE);
	printf("input base-16 string \"-0b%s\"\n", base2_string.chars);
	printf("function returned %d\n", ec);
	printf("value generated: " RASM_SSIZE_FMT "\n", ssize_value);

	puts("\n-- rasm_size_to_chars --");

	size_value = 1020304050;
	ec = rasm_size_to_chars(to_chars_buffer, size_value, RASM_BASE_10);
	printf("input size_value: " RASM_SIZE_FMT "\n", size_value);
	printf("function returned %d\n", ec);
	printf("base-10 string generated:%s\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	size_value = 0b10110101101;
	ec = rasm_size_to_chars(to_chars_buffer, size_value, RASM_BASE_2);
	printf("input size_value: " RASM_SIZE_FMT "\n", size_value);
	printf("function returned %d\n", ec);
	printf("base-2 string generated:%s\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	size_value = 0767676;
	ec = rasm_size_to_chars(to_chars_buffer, size_value, RASM_BASE_8);
	printf("input size_value: " RASM_SIZE_FMT "\n", size_value);
	printf("function returned %d\n", ec);
	printf("base-8 string generated:%s\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	size_value = 0xDEADBEEF;
	ec = rasm_size_to_chars(to_chars_buffer, size_value, RASM_BASE_16);
	printf("input size_value: " RASM_SIZE_FMT "\n", size_value);
	printf("function returned %d\n", ec);
	printf("base-16 string generated:%s\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	puts("\n-- rasm_ssize_to_chars --");

	ssize_value = -5040302010;
	ec = rasm_ssize_to_chars(to_chars_buffer, ssize_value, RASM_BASE_10);
	printf("input size_value: " RASM_SSIZE_FMT "\n", ssize_value);
	printf("function returned %d\n", ec);
	printf("base-10 string generated: \"%s\"\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	ssize_value = -0b110101101011;
	ec = rasm_ssize_to_chars(to_chars_buffer, ssize_value, RASM_BASE_2);
	printf("input size_value: " RASM_SSIZE_FMT "\n", ssize_value);
	printf("function returned %d\n", ec);
	printf("base-2 string generated: \"%s\"\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	ssize_value = -0676767;
	ec = rasm_ssize_to_chars(to_chars_buffer, ssize_value, RASM_BASE_8);
	printf("input size_value: " RASM_SSIZE_FMT "\n", ssize_value);
	printf("function returned %d\n", ec);
	printf("base-8 string generated: \"%s\"\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	ssize_value = -(rasm_ssize)0xBEEFDEAD;
	ec = rasm_ssize_to_chars(to_chars_buffer, ssize_value, RASM_BASE_16);
	printf("input size_value: " RASM_SSIZE_FMT "\n", ssize_value);
	printf("function returned %d\n", ec);
	printf("base-16 string generated: \"%s\"\n", to_chars_buffer.chars);
	memset(char_buffer, 0, sizeof char_buffer);

	return RASM_SUCCESS;
}
