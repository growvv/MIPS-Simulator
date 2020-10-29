#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include "registers.h"
#include "mips_sim.h"
#include<stdint.h>

//R type instruction
void add(int dest, int rs, int rt);
void sub(int dest, int rs, int rt);
void slt(int dest, int rs, int rt);
void mul(int dest, int rs, int rt);

// J type instruction
void beq(int rs, int rt, int imm);
void bne(int rs, int rt, int imm);
void addi(int rs, int rt, int imm);
void ori(int rs, int rt, int imm);
void lui(int rt, int imm);

// Syscall
void syscall();

#endif		//End of file