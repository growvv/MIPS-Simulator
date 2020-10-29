#include "operations.h"

void add(int dest, int rs, int rt)
{
	// 0: 0x34100004 ori  $16, $0, 4
	//printf("%d: 0x%08X add $%d, $%d, $%d\n", PC)
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[dest].val = a + b;
	PC++;
}
void sub(int dest, int rs, int rt)
{

	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[dest].val = a - b;
	PC++;
}
void slt(int dest, int rs, int rt)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[dest].val = a < b;
	PC++;
}
void mul(int dest, int rs, int rt)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[dest].val = a * b;
	PC++;
}

// J type instruction
void beq(int rs, int rt, int imm)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	if (a == b)
		PC += imm;
	else
		PC++;
}
void bne(int rs, int rt, int imm)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	if (a != b)
		PC += imm;
	else
		PC++;
}
void addi(int rs, int rt, int imm)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[rt].val = a + imm;
	PC++;
}
void ori(int rs, int rt, int imm)
{
	int a = reg_file[rs].val;
	int b = reg_file[rt].val;
	reg_file[rt].val = a | imm;
	PC++;
}
void lui(int rt, int imm)
{
	int a = reg_file[rt].val;
	reg_file[rt].val = imm << 16;
	PC++;
}

// Syscall
void syscall()
{
	if (reg_file[2].val == 1)		// if $v0=1, print integer
	{
		printf("<<< %d\n", reg_file[4].val);
	}
	else if (reg_file[2].val == 10)  // if $v0=10, exit
	{
		exit(0);
	}
	else if (reg_file[2].val == 11)	// if $v0=11, print character
	{
		printf("<<< %c\n", reg_file[4].val & 0xFF);
	}
	else
	{
		printf("Unknown system call: %d\n", reg_file[2].val);
	}
	PC++;
}