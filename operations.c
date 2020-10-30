#include "operations.h"

void add(int rd, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	// 0: 0x34100004 ori  $16, $0, 4
	if(trace_mode)  printf("%d: 0x%08X add  $%d, $%d, $%d\n", *PC, instructions[*PC], rd, rs, rt);
	int a = reg_file[rs];
	int b = reg_file[rt];
	reg_file[rd] = a + b;
	(*PC)++;
	if (trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd]);
}
void sub(int rd, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if(trace_mode)  printf("%d: 0x%08X sub  $%d, $%d, $%d\n", *PC, instructions[*PC], rd, rs, rt);
	int a = reg_file[rs];
	int b = reg_file[rt];
	reg_file[rd] = a - b;
	(*PC)++;
	if(trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd]);
}
void slt(int rd, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X slt  $%d, $%d, $%d\n", *PC, instructions[*PC], rd, rs, rt);
	int a = reg_file[rs];
	int b = reg_file[rt];
	reg_file[rd] = a < b;
	(*PC)++;
	if (trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd]);
}
void mul(int rd, int rs, int rt, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode) printf("%d: 0x%08X mul  $%d, $%d, $%d\n", *PC, instructions[*PC], rd, rs, rt);
	int a = reg_file[rs];
	int b = reg_file[rt];
	reg_file[rd] = a * b;
	(*PC)++;
	if (trace_mode) printf(">>> $%d = %d\n", rd, reg_file[rd]);
}

// J type instructions[*PC]
void beq(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X beq  $%d, $%d, %d\n", *PC, instructions[*PC], rs, rt, imm);
	int a = reg_file[rs];
	int b = reg_file[rt];
	if (a == b)
	{
		*PC += imm;
		if (trace_mode)  printf(">>> branch taken to PC = %d\n", *PC);
	}
	else
	{
		(*PC)++;
		if (trace_mode)  printf("branch not taken\n");
	}

}
void bne(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X bne  $%d, $%d, %d\n", *PC, instructions[*PC], rs, rt, imm);
	int a = reg_file[rs];
	int b = reg_file[rt];
	if (a != b)
	{
		*PC += imm;
		if (trace_mode)  printf(">>> branch taken to PC = %d\n", *PC);
	}
	else
	{
		(*PC)++;
		if (trace_mode)  printf("branch not taken\n");
	}
	
}
void addi(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X addi  $%d, $%d, %d\n", *PC, instructions[*PC], rt, rs, imm);
	int a = reg_file[rs];
	reg_file[rt] = a + imm;
	(*PC)++;
	if (trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt]);
}
void ori(int rs, int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X ori  $%d, $%d, %d\n", *PC, instructions[*PC], rt, rs, imm);
	int a = reg_file[rs];
	reg_file[rt] = a | imm;
	(*PC)++;
	if (trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt]);
}
void lui(int rt, int imm, int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X lui  $%d, %d\n", *PC, instructions[*PC], rt, imm);
	int a = reg_file[rt];
	reg_file[rt] = imm << 16;
	(*PC)++;
	if (trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt]);
}

// Syscall
void syscall(int trace_mode, int *PC, uint32_t *instructions, int *reg_file)
{
	if (trace_mode)  printf("%d: 0x%08X syscall\n", *PC, instructions[*PC]);
	if (trace_mode)  printf(">>> syscall %d\n", reg_file[2]);

	if (reg_file[2] == 1)		// if $v0=1, print integer
	{
		if(trace_mode)  printf("<<< %d\n", reg_file[4]);
		else  printf("%d", reg_file[4]);
	}
	else if (reg_file[2] == 10)  // if $v0=10, exit
	{
		exit(0);
	}
	else if (reg_file[2] == 11)	// if $v0=11, print character
	{
		if(trace_mode)  printf("<<< %c\n", ((reg_file)[4]) & 0xFF);
		else  printf("%c",((reg_file)[4]) & 0xFF);
	}
	else
	{
		printf("Unknown system call: %d\n", reg_file[2]);
		exit(1);
	}
	(*PC)++;
}