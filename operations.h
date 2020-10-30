#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

//R type instruction
void add(int dest, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void sub(int dest, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void slt(int dest, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void mul(int dest, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);

// J type instruction
void beq(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void bne(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void addi(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void ori(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);
void lui(int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file);

// Syscall
void syscall(int trace_mode, int *PC, uint32_t *instructions, int *reg_file);

#endif		//End of file