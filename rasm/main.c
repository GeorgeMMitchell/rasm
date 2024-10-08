#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <librasm/rasm.h>

#include <librasm/lib/debug.h>

struct args_state {
	const char **argv;
	int argc;
	int argi;
};

/* clang-format off */
static const char usage[] =
	"usage: %s [options] [source files]\n"
	"option syntax: \"-felf\", \"-f=elf\", \"-f elf\", \"-f= elf\"\n"
	"\n"
	"args:\n"
	"  --help,-h   prints program usage\n"
	"  --version   prints program version\n"
	"\n"
	"  --isa       [rv32i|rv64i]   sets target CPU architecture\n"
	"  --format,-f [bin|elf]       sets object format\n";
/* clang-format on */

static const char *main_process_name;

static void
rasm_print(FILE *stream, const char *format, ...)
{
	va_list va;

	RASM_DEBUG_ASSERT(format);

	va_start(va, format);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"

#ifdef RASM_DEBUG
	if (vfprintf(stream, format, va) < 0) {
		va_end(va);

		perror("vfprintf failure");

		exit(errno);
	}
#else
	vfprintf(stream, format, va);
#endif

#pragma clang diagnostic pop

	va_end(va);
}

static void
print_error(struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(error);

	rasm_print(stderr, "%s: ", main_process_name);

	if (error->file.name) {
		rasm_print(stderr, "%s", error->file.name);

		if (error->file.line) {
			rasm_print(
			  stderr, ":" RASM_SIZE_FMT ": ", error->file.line);
		} else {
			rasm_print(stderr, " ");
		}
	}

	rasm_print(stderr, "error: ");

	if (*error->message) { rasm_print(stderr, "%s", error->message); }

	exit(RASM_FAILURE);
}

static void
print_version(FILE *stream)
{
	rasm_print(stream, "%d.%d.%d\n", RASM_VERSION_MAJOR,
	  RASM_VERSION_MINOR, RASM_VERSION_PATCH);
}

static void
print_usage(FILE *stream)
{
	rasm_print(stream, "rasm version ");

	print_version(stream);

	rasm_print(stream, "%s\n", usage);
}

static void
get_opt_val(const char **val, int optlen, struct args_state *args,
  struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(val);
	RASM_DEBUG_ASSERT(0 < optlen);
	RASM_DEBUG_ASSERT(args);
	RASM_DEBUG_ASSERT(error);

	*val = args->argv[args->argi] + optlen;

	if (**val == '=') { ++*val; }

	if (**val == '\0') {
		if (args->argi + 1 == args->argc) {
			rasm_error_message(error, "%s: missing option value",
			  args->argv[args->argi]);

			print_error(error);
		}

		*val = args->argv[++args->argi];
	}
}

static void
shift_opt(int valc, struct args_state *args, struct rasm_input *input)
{
	const char *src, **srcp;
	unsigned optvalc;

	RASM_DEBUG_ASSERT(0 <= valc);
	RASM_DEBUG_ASSERT(args);
	RASM_DEBUG_ASSERT(input);

	srcp = args->argv + args->argi - valc - 1;

	optvalc = (unsigned)valc + 1;

	do {
		src = *srcp;

		memmove(srcp, srcp + 1, optvalc);

		srcp[optvalc] = src;

	} while (input->srcv <= srcp--);

	input->srcv += optvalc;
}

static void
set_input_format(
  const char *fmt, struct rasm_input *input, struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(fmt);
	RASM_DEBUG_ASSERT(input);
	RASM_DEBUG_ASSERT(error);

	if (!strncmp(fmt, "bin", 3)) {
		input->format = RASM_FMT_BIN;

	} else if (!strncmp(fmt, "elf", 3)) {
		input->format = RASM_FMT_ELF;

	} else {
		rasm_error_message(error, "%s: unknown object format", fmt);

		print_error(error);
	}
}

static void
set_input_isa(
  const char *isa, struct rasm_input *input, struct rasm_error *error)
{
	RASM_DEBUG_ASSERT(isa);
	RASM_DEBUG_ASSERT(input);
	RASM_DEBUG_ASSERT(error);

	if (!strncmp(isa, "rv32i", 5)) {
		input->isa = RASM_ISA_RV32I;

	} else if (!strncmp(isa, "rv64i", 5)) {
		input->isa = RASM_ISA_RV64I;

	} else {
		rasm_error_message(error, "%s: missing option value", isa);

		print_error(error);
	}
}

static void
parse_option(
  struct args_state *args, struct rasm_input *input, struct rasm_error *error)
{
	const char *arg, *opt, *val;

	int argi_old;

	RASM_DEBUG_ASSERT(args);
	RASM_DEBUG_ASSERT(input);
	RASM_DEBUG_ASSERT(error);

	argi_old = args->argi;

	arg = args->argv[argi_old];

	switch (arg[1]) {
		case 'h':
			print_usage(stdout);

			exit(RASM_SUCCESS);

		case 'f':
			get_opt_val(&val, 2, args, error);

			set_input_format(val, input, error);

			break;

		case '-':
			opt = arg + 2;

			if (!strncmp(opt, "help", 5)) {
				print_usage(stdout);

				exit(RASM_SUCCESS);
			}

			if (!strncmp(opt, "version", 7)) {
				print_version(stdout);

				exit(RASM_SUCCESS);
			}

			if (!strncmp(opt, "isa", 3)) {
				get_opt_val(&val, 5, args, error);

				set_input_isa(val, input, error);

				break;
			}

			if (!strncmp(opt, "format", 6)) {
				get_opt_val(&val, 8, args, error);

				set_input_format(val, input, error);

				break;
			}

		default:
			rasm_error_message(error, "%s: unknown option", arg);

			print_error(error);
	}

	if (input->srcv) { shift_opt(args->argi - argi_old, args, input); }
}

int
main(int argc, const char **argv)
{
	struct rasm_context ctx;
	struct rasm_input input;
	struct args_state args;

	RASM_DEBUG_ASSERT(0 < argc && argv && *argv);

	main_process_name = *argv;

	if (argc < 2) {
		print_usage(stdout);

		return RASM_SUCCESS;
	}

	args.argv = argv;
	args.argc = argc;
	args.argi = 1;

	do {
		if (argv[args.argi][0] == '-') {
			parse_option(&args, &input, &ctx.error);

		} else if (input.srcc) {
			++input.srcc;

		} else {
			input.srcv = args.argv + args.argi;
			input.srcc = 1;
		}

	} while (++args.argi < argc);

	if (rasm_assemble(&input, &ctx) == RASM_FAILURE) {
		print_error(&ctx.error);

		return RASM_FAILURE;
	}

	return RASM_SUCCESS;
}
