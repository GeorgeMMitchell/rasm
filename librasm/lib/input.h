#ifndef RASM_INPUT_H
#define RASM_INPUT_H

enum rasm_input_format { RASM_FMT_ELF, RASM_FMT_BIN };

enum rasm_input_isa { RASM_ISA_RV64I, RASM_ISA_RV32I };

struct rasm_input {
	enum rasm_input_format format;
	enum rasm_input_isa isa;
	const char *program_path;
	const char **srcv;
	int srcc;
};

#endif
