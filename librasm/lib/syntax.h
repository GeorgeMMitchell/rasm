#ifndef RASM_SYNTAX_H
#define RASM_SYNTAX_H

#include <librasm/lib/token.h>

struct rasm_syntax_instruction {
  struct rasm_token opcode;
  struct rasm_token arg1;
  struct rasm_token arg2;
};

#endif
