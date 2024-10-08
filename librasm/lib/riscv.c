/*
 * Copyright (c) 2024 - present George Mitchell
 * SPDX-License-Identifier: 0BSD
 */

#include <librasm/lib/riscv.h>

#include <librasm/lib/debug.h>

struct rasm_rv32i_instr_r
rasm_rv32i_instr_r_init(rasm_uint8 src1, rasm_uint8 src2, rasm_uint8 dst,
  rasm_uint8 funct7, rasm_uint8 funct3, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_r r;

	r.funct7 = (unsigned)funct7 & 0x7Fu;
	r.rs2	 = (unsigned)src2 & 0x1Fu;
	r.rs1	 = (unsigned)src1 & 0x1Fu;
	r.funct3 = (unsigned)funct3 & 0x3u;
	r.rd	 = (unsigned)dst & 0x1Fu;
	r.opcode = (unsigned)opcode & 0x7Fu;

	return r;
}

struct rasm_rv32i_instr_i
rasm_rv32i_instr_i_init(rasm_uint16 imm12, rasm_uint8 src, rasm_uint8 dst,
  rasm_uint8 funct3, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_i i;

	RASM_DEBUG_ASSERT(!(imm12 & 0xF000u));

	i.imm11_0 = (unsigned)imm12 & 0xFFFu;
	i.rs1	  = (unsigned)src & 0x1Fu;
	i.funct3  = (unsigned)funct3 & 0x3u;
	i.rd	  = (unsigned)dst & 0x1Fu;
	i.opcode  = (unsigned)opcode & 0x7Fu;

	return i;
}

struct rasm_rv32i_instr_s
rasm_rv32i_instr_s_init(rasm_uint16 off12, rasm_uint8 src, rasm_uint8 base,
  rasm_uint8 funct3, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_s s;

	RASM_DEBUG_ASSERT(!(off12 & 0xF000u));

	s.imm11_5 = (unsigned)(off12 & 0x07F0u) >> 4u;
	s.rs2	  = (unsigned)src & 0x1Fu;
	s.rs1	  = (unsigned)base & 0x1Fu;
	s.funct3  = (unsigned)funct3 & 0x3u;
	s.imm4_0  = (unsigned)off12 & 0x000Fu;
	s.opcode  = (unsigned)opcode & 0x7Fu;

	return s;
}

struct rasm_rv32i_instr_b
rasm_rv32i_instr_b_init(rasm_uint16 off12, rasm_uint8 src1, rasm_uint8 src2,
  rasm_uint8 funct3, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_b b;

	RASM_DEBUG_ASSERT(!(off12 & 0xF000u));

	b.imm12	  = (unsigned)(off12 & 0x0800u) >> 11u;
	b.imm10_5 = (unsigned)(off12 & 0x03F0u) >> 4u;
	b.rs2	  = (unsigned)src2 & 0x1Fu;
	b.rs1	  = (unsigned)src1 & 0x1Fu;
	b.funct3  = (unsigned)funct3 & 0x3u;
	b.imm4_1  = (unsigned)off12 & 0x000Fu;
	b.imm11	  = (unsigned)(off12 & 0x0400u) >> 10u;
	b.opcode  = (unsigned)opcode & 0x7Fu;

	return b;
}

struct rasm_rv32i_instr_u
rasm_rv32i_instr_u_init(rasm_uint32 imm20, rasm_uint8 dst, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_u u;

	RASM_DEBUG_ASSERT(!(imm20 & 0xFFF00000u));

	u.imm31_12 = (unsigned)imm20 & 0xFFFFFu;
	u.rd	   = (unsigned)dst & 0x1Fu;
	u.opcode   = (unsigned)opcode & 0x7Fu;

	return u;
}

struct rasm_rv32i_instr_j
rasm_rv32i_instr_j_init(rasm_uint32 off20, rasm_uint8 dst, rasm_uint8 opcode)
{
	struct rasm_rv32i_instr_j j;

	RASM_DEBUG_ASSERT(!(off20 & 0xFFF00000u));

	j.imm20	   = (unsigned)(off20 & 0x00080000u) >> 19u;
	j.imm10_1  = (unsigned)(off20 & 0x000007FEu) >> 1u;
	j.imm11	   = (unsigned)(off20 & 0x00000400u) >> 10u;
	j.imm19_12 = (unsigned)(off20 & 0x0007F800u) >> 11u;
	j.rd	   = (unsigned)dst & 0x1Fu;
	j.opcode   = (unsigned)opcode & 0x7Fu;

	return j;
}

struct rasm_rv32i_instr_shift
rasm_rv32i_instr_shift_init(rasm_uint8 shamt5, rasm_uint8 src, rasm_uint8 dst,
  rasm_uint8 shtype, rasm_uint8 funct3)
{
	struct rasm_rv32i_instr_shift s;

	RASM_DEBUG_ASSERT(!(shamt5 & 0xE0u));

	s.imm11_5 = (unsigned)shtype & 0x7Fu;
	s.imm4_0  = (unsigned)shamt5 & 0x1Fu;
	s.rs1	  = (unsigned)src & 0x1Fu;
	s.funct3  = (unsigned)funct3 & 0x3u;
	s.rd	  = (unsigned)dst & 0x1Fu;
	s.opcode  = (unsigned)RASM_OPCODE_OP;

	return s;
}
