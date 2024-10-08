/*
 * Copyright (c) 2024 - present George Mitchell
 * SPDX-License-Identifier: 0BSD
 */

#ifndef RASM_RISCV_H
#define RASM_RISCV_H

#include <librasm/lib/api.h>
#include <librasm/lib/number.h>

/* clang-format off */
enum rasm_int_register {
	RASM_X0_ZERO,

	RASM_X1_RA,
	RASM_X2_SP,
	RASM_X3_GP,
	RASM_X4_TP,

	RASM_X5_T0, RASM_X6_T1, RASM_X7_T2,

	RASM_X8_S0_FP, RASM_X9_S1,

	RASM_X10_A0, RASM_X11_A1, RASM_X12_A2, RASM_X13_A3,
	RASM_X14_A4, RASM_X15_A5, RASM_X16_A6, RASM_X17_A7,

	RASM_X18_S2, RASM_X19_S3, RASM_X20_S4, RASM_X21_S5,
	RASM_X22_S6, RASM_X23_S7, RASM_X24_S8, RASM_X25_S9,
	RASM_X26_S10, RASM_X27_S11,

	RASM_X28_T3, RASM_X29_T4, RASM_X30_T5, RASM_X31_T6
};

enum rasm_cpu_float_reg {
	RASM_F0_FT0, RASM_F1_FT1, RASM_F2_FT2, RASM_F3_FT3,
	RASM_F4_FT4, RASM_F5_FT5, RASM_F6_FT6, RASM_F7_FT7,

	RASM_F8_FS0, RASM_F9_FS1,

	RASM_F10_FA0, RASM_F11_FA1, RASM_F12_FA2, RASM_F13_FA3,
	RASM_F14_FA4, RASM_F15_FA5, RASM_F16_FA6, RASM_F17_FA7,

	RASM_F18_FS2, RASM_F19_FS3, RASM_F20_FS4, RASM_F21_FS5,
	RASM_F22_FS6, RASM_F23_FS7, RASM_F24_FS8, RASM_F25_FS9,
	RASM_F26_FS10, RASM_F27_FS11,

	RASM_F28_FT8, RASM_F29_FT9, RASM_F30_FT10, RASM_F31_FT11
};

#if 0
enum rasm_rv32i_instr_type{
	RASM_RV32I_INSTR_UNK,

	RASM_RV32I_INSTR_NOP, RASM_RV32I_INSTR_ECALL, RASM_RV32I_INSTR_EBREAK,

	RASM_RV32I_INSTR_ADDI, RASM_RV32I_INSTR_SLTI, RASM_RV32I_INSTR_SLTIU, RASM_RV32I_INSTR_ANDI,
	RASM_RV32I_INSTR_ORI, RASM_RV32I_INSTR_XORI, RASM_RV32I_INSTR_SLLI, RASM_RV32I_INSTR_SRLI,
	RASM_RV32I_INSTR_SRAI, RASM_RV32I_INSTR_LUI,

	RASM_RV32I_INSTR_AUIPC,
	RASM_RV32I_INSTR_ADD,
	RASM_RV32I_INSTR_SLT, RASM_RV32I_INSTR_SLTU,
	RASM_RV32I_INSTR_AND,
	RASM_RV32I_INSTR_OR, RASM_RV32I_INSTR_XOR,
	RASM_RV32I_INSTR_SLL, RASM_RV32I_INSTR_SRL, RASM_RV32I_INSTR_SUB, RASM_RV32I_INSTR_SRA,

	RASM_RV32I_INSTR_JAL, RASM_RV32I_INSTR_JALR,

	RASM_RV32I_INSTR_BEQ, RASM_RV32I_INSTR_BNE,
	RASM_RV32I_INSTR_BLT, RASM_RV32I_INSTR_BLTU,
	RASM_RV32I_INSTR_BGE, RASM_RV32I_INSTR_BGEU,

	RASM_RV32I_INSTR_LB, RASM_RV32I_INSTR_LH, RASM_RV32I_INSTR_LW,
	RASM_RV32I_INSTR_LBU, RASM_RV32I_INSTR_LHU,

	RASM_RV32I_INSTR_SB, RASM_RV32I_INSTR_SH, RASM_RV32I_INSTR_SW,

	RASM_RV32I_INSTR_CSRRW, RASM_RV32I_INSTR_CSRRS, RASM_RV32I_INSTR_CSRRC,
	RASM_RV32I_INSTR_CSRRWI, RASM_RV32I_INSTR_CSRRSI, RASM_RV32I_INSTR_CSRRCI
};
#endif

enum rasm_rv32i_instr_format {
	RASM_RV32I_INSTR_FORMAT_NONE,

	RASM_RV32I_INSTR_FORMAT_R, RASM_RV32I_INSTR_FORMAT_I, RASM_RV32I_INSTR_FORMAT_S,
	RASM_RV32I_INSTR_FORMAT_B, RASM_RV32I_INSTR_FORMAT_U, RASM_RV32I_INSTR_FORMAT_J,

	RASM_RV32I_INSTR_FORMAT_SHIFT
};
/* clang-format on */

enum rasm_opcode {
	RASM_OPCODE_LOAD      = 0x03,
	RASM_OPCODE_LOAD_FP   = 0x07,
	RASM_OPCODE_CUSTOM_0  = 0x0B,
	RASM_OPCODE_MISC_MEM  = 0x0F,
	RASM_OPCODE_OP_IMM    = 0x13,
	RASM_OPCODE_AUIPC     = 0x17,
	RASM_OPCODE_OP_IMM_32 = 0x1B,

	RASM_OPCODE_STORE    = 0x23,
	RASM_OPCODE_STORE_FP = 0x27,
	RASM_OPCODE_CUSTOM_1 = 0x2B,
	RASM_OPCODE_AMO	     = 0x2F,
	RASM_OPCODE_OP	     = 0x33,
	RASM_OPCODE_LUI	     = 0x37,
	RASM_OPCODE_OP_32    = 0x3B,

	RASM_OPCODE_MADD	   = 0x43,
	RASM_OPCODE_MSUB	   = 0x47,
	RASM_OPCODE_NMSUB	   = 0x4B,
	RASM_OPCODE_NMADD	   = 0x4F,
	RASM_OPCODE_OP_FP	   = 0x53,
	RASM_OPCODE_RESERVED_0	   = 0x57,
	RASM_OPCODE_CUSTOM_2_RV128 = 0x5B,

	RASM_OPCODE_BRANCH	   = 0x63,
	RASM_OPCODE_JALR	   = 0x67,
	RASM_OPCODE_RESERVED_1	   = 0x6B,
	RASM_OPCODE_JAL		   = 0x6F,
	RASM_OPCODE_SYSTEM	   = 0x73,
	RASM_OPCODE_RESERVED_2	   = 0x77,
	RASM_OPCODE_CUSTOM_3_RV128 = 0x7B
};

enum rasm_opcode_i_funct3 {
	RASM_OPCODE_FUNCT3_JALR = 0x0,

	RASM_OPCODE_FUNCT3_ADDI	 = 0x0,
	RASM_OPCODE_FUNCT3_SLTI	 = 0x2,
	RASM_OPCODE_FUNCT3_SLTIU = 0x3,
	RASM_OPCODE_FUNCT3_ANDI	 = 0x7,
	RASM_OPCODE_FUNCT3_ORI	 = 0x6,
	RASM_OPCODE_FUNCT3_XORI	 = 0x4,

	RASM_OPCODE_FUNCT3_SRLI = 0x5,
	RASM_OPCODE_FUNCT3_SLLI = 0x1,
	RASM_OPCODE_FUNCT3_SRAI = 0x5,

	RASM_OPCODE_FUNCT3_CSRRW  = 0x1,
	RASM_OPCODE_FUNCT3_CSRRS  = 0x2,
	RASM_OPCODE_FUNCT3_CSRRC  = 0x3,
	RASM_OPCODE_FUNCT3_CSRRWI = 0x5,
	RASM_OPCODE_FUNCT3_CSRRSI = 0x6,
	RASM_OPCODE_FUNCT3_CSRRCI = 0x7,
	RASM_OPCODE_FUNCT3_PRIV	  = 0x0,

	RASM_OPCODE_FUNCT3_LB  = 0x0,
	RASM_OPCODE_FUNCT3_LH  = 0x1,
	RASM_OPCODE_FUNCT3_LW  = 0x2,
	RASM_OPCODE_FUNCT3_LBU = 0x4,
	RASM_OPCODE_FUNCT3_LHU = 0x5
};

enum rasm_opcode_i_funct12 {
	RASM_OPCODE_FUNCT12_ECALL  = 0x0,
	RASM_OPCODE_FUNCT12_EBREAK = 0x1
};

enum rasm_opcode_shift_shtype {
	RASM_OPCODE_SHTYPE_SRLI = 0x0,
	RASM_OPCODE_SHTYPE_SLLI = 0x0,
	RASM_OPCODE_SHTYPE_SRAI = 0x20
};

enum rasm_opcode_r_funct3 {
	RASM_OPCODE_FUNCT3_ADD	= 0x0,
	RASM_OPCODE_FUNCT3_SUB	= 0x0,
	RASM_OPCODE_FUNCT3_SLL	= 0x1,
	RASM_OPCODE_FUNCT3_SLT	= 0x2,
	RASM_OPCODE_FUNCT3_SLTU = 0x3,
	RASM_OPCODE_FUNCT3_XOR	= 0x4,
	RASM_OPCODE_FUNCT3_SRL	= 0x5,
	RASM_OPCODE_FUNCT3_SRA	= 0x5,
	RASM_OPCODE_FUNCT3_OR	= 0x6,
	RASM_OPCODE_FUNCT3_AND	= 0x7
};

enum rasm_opcode_r_funct7 {
	RASM_OPCODE_FUNCT7_ADD	= 0x0,
	RASM_OPCODE_FUNCT7_SUB	= 0x20,
	RASM_OPCODE_FUNCT7_SLL	= 0x0,
	RASM_OPCODE_FUNCT7_SLT	= 0x0,
	RASM_OPCODE_FUNCT7_SLTU = 0x0,
	RASM_OPCODE_FUNCT7_XOR	= 0x0,
	RASM_OPCODE_FUNCT7_SRL	= 0x0,
	RASM_OPCODE_FUNCT7_SRA	= 0x20,
	RASM_OPCODE_FUNCT7_OR	= 0x0,
	RASM_OPCODE_FUNCT7_AND	= 0x0
};

enum rasm_opcode_s_funct3 {
	RASM_OPCODE_FUNCT3_SB = 0x0,
	RASM_OPCODE_FUNCT3_SH = 0x1,
	RASM_OPCODE_FUNCT3_SW = 0x2
};

enum rasm_opcode_b_funct3 {
	RASM_OPCODE_FUNCT3_BEQ	= 0x0,
	RASM_OPCODE_FUNCT3_BNE	= 0x1,
	RASM_OPCODE_FUNCT3_BLT	= 0x4,
	RASM_OPCODE_FUNCT3_BLTU = 0x6,
	RASM_OPCODE_FUNCT3_BGE	= 0x5,
	RASM_OPCODE_FUNCT3_BGEU = 0x7
};

struct rasm_rv32i_instr_r {
	unsigned funct7 : 7;
	unsigned rs2	: 5;
	unsigned rs1	: 5;
	unsigned funct3 : 3;
	unsigned rd	: 5;
	unsigned opcode : 7;
};

struct rasm_rv32i_instr_i {
	unsigned imm11_0 : 12;
	unsigned rs1	 : 5;
	unsigned funct3	 : 3;
	unsigned rd	 : 5;
	unsigned opcode	 : 7;
};

struct rasm_rv32i_instr_s {
	unsigned imm11_5 : 7;
	unsigned rs2	 : 5;
	unsigned rs1	 : 5;
	unsigned funct3	 : 3;
	unsigned imm4_0	 : 5;
	unsigned opcode	 : 7;
};

struct rasm_rv32i_instr_b {
	unsigned imm12	 : 1;
	unsigned imm10_5 : 6;
	unsigned rs2	 : 5;
	unsigned rs1	 : 5;
	unsigned funct3	 : 3;
	unsigned imm4_1	 : 4;
	unsigned imm11	 : 1;
	unsigned opcode	 : 7;
};

struct rasm_rv32i_instr_u {
	unsigned imm31_12 : 20;
	unsigned rd	  : 5;
	unsigned opcode	  : 7;
};

struct rasm_rv32i_instr_j {
	unsigned imm20	  : 1;
	unsigned imm10_1  : 10;
	unsigned imm11	  : 1;
	unsigned imm19_12 : 8;
	unsigned rd	  : 5;
	unsigned opcode	  : 7;
};

struct rasm_rv32i_instr_shift {
	unsigned imm11_5 : 7;
	unsigned imm4_0	 : 5;
	unsigned rs1	 : 5;
	unsigned funct3	 : 3;
	unsigned rd	 : 5;
	unsigned opcode	 : 7;
};

#if 0
union rasm_rv32i_instruction_value {
	struct rasm_rv32i_instr_r r;
	struct rasm_rv32i_instr_i i;
	struct rasm_rv32i_instr_s s;
	struct rasm_rv32i_instr_b b;
	struct rasm_rv32i_instr_u u;
	struct rasm_rv32i_instr_j j;

	struct rasm_rv32i_instr_shift shift;

	rasm_uint32 bytes;

};
#endif

RASM_API struct rasm_rv32i_instr_r rasm_rv32i_instr_r_init(
  rasm_uint8 /* src1 */, rasm_uint8 /* src2 */, rasm_uint8 /* dst */,
  rasm_uint8 /* funct7 */, rasm_uint8 /* funct3 */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_i rasm_rv32i_instr_i_init(
  rasm_uint16 /* imm12 */, rasm_uint8 /* src */, rasm_uint8 /* dst */,
  rasm_uint8 /* funct3 */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_s rasm_rv32i_instr_s_init(
  rasm_uint16 /* off12 */, rasm_uint8 /* src */, rasm_uint8 /* base */,
  rasm_uint8 /* funct3 */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_b rasm_rv32i_instr_b_init(
  rasm_uint16 /* off12 */, rasm_uint8 /* src1 */, rasm_uint8 /* src2 */,
  rasm_uint8 /* funct3 */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_u rasm_rv32i_instr_u_init(
  rasm_uint32 /* imm20 */, rasm_uint8 /* dst */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_j rasm_rv32i_instr_j_init(
  rasm_uint32 /* off20 */, rasm_uint8 /* dst */, rasm_uint8 /* opcode */);

RASM_API struct rasm_rv32i_instr_shift rasm_rv32i_instr_shift_init(
  rasm_uint8 /* shamt5 */, rasm_uint8 /* src */, rasm_uint8 /* dst */,
  rasm_uint8 /* shtype */, rasm_uint8 /* funct3 */);

#define RASM_RV32I_INSTR_ADDI(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_ADDI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_SLTI(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_SLTI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_SLTIU(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_SLTIU, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_ANDI(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_ANDI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_ORI(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_ORI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_XORI(imm12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  imm12, src, dst, RASM_OPCODE_FUNCT3_XORI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_SLLI(shamt5, src, dst) \
	rasm_rv32i_instr_shift_init( \
	  shamt5, src, dst, RASM_OPCODE_SHTYPE_SLLI, RASM_OPCODE_FUNCT3_SLLI)

#define RASM_RV32I_INSTR_SRLI(shamt5, src, dst) \
	rasm_rv32i_instr_shift_init( \
	  shamt5, src, dst, RASM_OPCODE_SHTYPE_SRLI, RASM_OPCODE_FUNCT3_SRLI)

#define RASM_RV32I_INSTR_SRAI(shamt5, src, dst) \
	rasm_rv32i_instr_shift_init( \
	  shamt5, src, dst, RASM_OPCODE_SHTYPE_SRAI, RASM_OPCODE_FUNCT3_SRAI)

#define RASM_RV32I_INSTR_LUI(imm20, dst) \
	rasm_rv32i_instr_u_init(imm20, dst, RASM_OPCODE_LUI)

#define RASM_RV32I_INSTR_AUIPC(imm20, dst) \
	rasm_rv32i_instr_u_init(imm20, dst, RASM_OPCODE_AUIPC)

#define RASM_RV32I_INSTR_NOP() \
	rasm_rv32i_instr_i_init(0u, RASM_X0_ZERO, RASM_X0_ZERO, \
	  RASM_OPCODE_FUNCT3_ADDI, RASM_OPCODE_OP_IMM)

#define RASM_RV32I_INSTR_ADD(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_ADD, \
	  RASM_OPCODE_FUNCT3_ADD, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SLT(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SLT, \
	  RASM_OPCODE_FUNCT3_SLT, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SLTU(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SLTU, \
	  RASM_OPCODE_FUNCT3_SLTU, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_AND(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_AND, \
	  RASM_OPCODE_FUNCT3_AND, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_OR(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_OR, \
	  RASM_OPCODE_FUNCT3_OR, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_XOR(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_XOR, \
	  RASM_OPCODE_FUNCT3_XOR, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SLL(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SLL, \
	  RASM_OPCODE_FUNCT3_SLL, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SRL(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SRL, \
	  RASM_OPCODE_FUNCT3_SRL, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SUB(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SUB, \
	  RASM_OPCODE_FUNCT3_SUB, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_SRA(src1, src2, dst) \
	rasm_rv32i_instr_r_init(src1, src2, dst, RASM_OPCODE_FUNCT7_SRA, \
	  RASM_OPCODE_FUNCT3_SRA, RASM_OPCODE_OP)

#define RASM_RV32I_INSTR_JAL(off20, dst) \
	rasm_rv32i_instr_j_init(off20, dst, RASM_OPCODE_JAL)

#define RASM_RV32I_INSTR_JALR(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_JALR, RASM_OPCODE_JALR)

#define RASM_RV32I_INSTR_BEQ(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BEQ, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_BNE(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BNE, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_BLT(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BLT, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_BLTU(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BLTU, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_BGE(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BGE, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_BGEU(off12, src1, src2) \
	rasm_rv32i_instr_b_init( \
	  off12, src1, src2, RASM_OPCODE_FUNCT3_BGEU, RASM_OPCODE_BRANCH)

#define RASM_RV32I_INSTR_LB(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_LB, RASM_OPCODE_LOAD)

#define RASM_RV32I_INSTR_LH(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_LH, RASM_OPCODE_LOAD)

#define RASM_RV32I_INSTR_LW(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_LW, RASM_OPCODE_LOAD)

#define RASM_RV32I_INSTR_LBU(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_LBU, RASM_OPCODE_LOAD)

#define RASM_RV32I_INSTR_LHU(off12, base, dst) \
	rasm_rv32i_instr_i_init( \
	  off12, base, dst, RASM_OPCODE_FUNCT3_LHU, RASM_OPCODE_LOAD)

#define RASM_RV32I_INSTR_SB(off12, src, base) \
	rasm_rv32i_instr_s_init( \
	  off12, src, base, RASM_OPCODE_FUNCT3_SB, RASM_OPCODE_STORE)

#define RASM_RV32I_INSTR_SH(off12, src, base) \
	rasm_rv32i_instr_s_init( \
	  off12, src, base, RASM_OPCODE_FUNCT3_SH, RASM_OPCODE_STORE)

#define RASM_RV32I_INSTR_SW(off12, src, base) \
	rasm_rv32i_instr_s_init( \
	  off12, src, base, RASM_OPCODE_FUNCT3_SW, RASM_OPCODE_STORE)

#define RASM_RV32I_INSTR_CSRRW(srcdst12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  srcdst12, src, dst, RASM_OPCODE_FUNCT3_CSRRW, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_CSRRS(srcdst12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  srcdst12, src, dst, RASM_OPCODE_FUNCT3_CSRRS, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_CSRRC(srcdst12, src, dst) \
	rasm_rv32i_instr_i_init( \
	  srcdst12, src, dst, RASM_OPCODE_FUNCT3_CSRRC, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_CSRRWI(srcdst12, uimm_5, dst) \
	rasm_rv32i_instr_i_init(srcdst12, uimm_5, dst, \
	  RASM_OPCODE_FUNCT3_CSRRWI, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_CSRRSI(srcdst12, uimm_5, dst) \
	rasm_rv32i_instr_i_init(srcdst12, uimm_5, dst, \
	  RASM_OPCODE_FUNCT3_CSRRSI, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_CSRRCI(srcdst12, uimm_5, dst) \
	rasm_rv32i_instr_i_init(srcdst12, uimm_5, dst, \
	  RASM_OPCODE_FUNCT3_CSRRCI, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_ECALL() \
	rasm_rv32i_instr_i_init(RASM_OPCODE_FUNCT12_ECALL, RASM_X0_ZERO, \
	  RASM_X0_ZERO, RASM_OPCODE_FUNCT3_PRIV, RASM_OPCODE_SYSTEM)

#define RASM_RV32I_INSTR_EBREAK() \
	rasm_rv32i_instr_i_init(RASM_OPCODE_FUNCT12_EBREAK, RASM_X0_ZERO, \
	  RASM_X0_ZERO, RASM_OPCODE_FUNCT3_PRIV, RASM_OPCODE_SYSTEM)

#endif
