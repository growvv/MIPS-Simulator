// COMP1521 20T3 Assignment 1: mips_sim -- a MIPS simulator
// starting point code v0.1 - 13/10/20


// PUT YOUR HEADER COMMENT HERE


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "operations.h"


#define MAX_LINE_LENGTH 256
#define INSTRUCTIONS_GROW 64


// ADD YOUR #defines HERE

// Defining opcodes/func
#define ADD 0b100000		//ADD   => 32
#define SUB 0b100010		//SUB   => 34
#define SLT 0b101010		//SLT   => 42
#define MUL_op    0b011100		// MUL_op = 28
#define MUL_funct 0b000010		// MUL_funt = 2
#define BEQ  0b000100		//BEQ   => 4	
#define BNE  0b000101		//BEQ   => 5	
#define ADDI 0b001000		//ADDI  => 8
#define	ORI  0b001101		//ORI   => 13	
#define LUI  0b001111		//LUI   => 15	
#define SYSCALL 0b001100	//SYSCALL=>12	

void execute_instructions(int n_instructions,
	uint32_t* instructions,
	int trace_mode);
char *process_arguments(int argc, char *argv[], int *trace_mode);
uint32_t *read_instructions(char *filename, int *n_instructions_p);
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions);


// ADD YOUR FUNCTION PROTOTYPES HERE
int16_t get_complement(int16_t imm);
void execute_single(uint32_t* instructions, int trace_mode, int *PC, int *reg_file);


// YOU SHOULD NOT NEED TO CHANGE MAIN

int main(int argc, char *argv[]) {
	int trace_mode;
	char *filename = process_arguments(argc, argv, &trace_mode);

	int n_instructions;
	uint32_t *instructions = read_instructions(filename, &n_instructions);

	execute_instructions(n_instructions, instructions, trace_mode);

	free(instructions);
	return 0;
}


// simulate execution of  instruction codes in  instructions array
// output from syscall instruction & any error messages are printed
//
// if trace_mode != 0:
//     information is printed about each instruction as it executed
//
// execution stops if it reaches the end of the array

void execute_instructions(int n_instructions,
	uint32_t *instructions,
	int trace_mode) {

	int reg_file[32];
	int PC = 0;
	for (int i = 0; i < 32; i++)
		reg_file[i] = 0;

	while (PC < n_instructions && PC >= 0) {
		execute_single(instructions, trace_mode, &PC, reg_file);
	}
}



// ADD YOUR FUNCTIONS HERE

int16_t get_complement(int16_t imm)
{
	if (imm < 0)
		imm = (~(-imm)) + 1;
	return imm;
}

void execute_single(uint32_t* instructions, int trace_mode, int *PC, int *reg_file)
{
	uint32_t instruction = instructions[*PC];
	int op = instruction >> 26;
	int rs = (instruction >> 21) & 0x1F;
	int rt = (instruction >> 16) & 0x1F;
	int rd = (instruction >> 11) & 0x1F;
	int shamt = (instruction >> 6) & 0x1F;
	int funct = instruction & 0x3F;

	int imm = get_complement(instruction & 0xFFFF);

	switch (op)     // according to opcode and funct
	{
	case 0:
		if (shamt != 0)
		{
			if(trace_mode)  printf("%d: 0x%08X invalid instruction code\n", *PC, instruction);
			else   printf("invalid instruction code\n");
			//break;
			exit(1);
		}
		switch (funct)
		{
		case ADD:
			add(rd, rs, rt, trace_mode, PC, instructions, reg_file);
			break;
		case SUB:
			sub(rd, rs, rt, trace_mode, PC, instructions, reg_file);
			break;
		case SLT:
			slt(rd, rs, rt, trace_mode, PC, instructions, reg_file);
			break;
		case SYSCALL:
			if (rs == 0 && rt == 0 && rd == 0 && shamt == 0)
				syscall(trace_mode, PC, instructions, reg_file);
			else
			{
				if(trace_mode)  printf("%d: 0x%08X invalid instruction code\n", *PC, instruction);
				else   printf("invalid instruction code\n");
				exit(1);
			}
			break;
		default:
			if(trace_mode)  printf("%d: 0x%08X invalid instruction code\n", *PC, instruction);
			else   printf("invalid instruction code\n");
			//break;
			exit(1);
		}
		break;
	case MUL_op:
		if (shamt == 0 && funct == MUL_funct)
			mul(rd, rs, rt, trace_mode, PC, instructions, reg_file);
		else
		{
			if(trace_mode)  printf("%d: 0x%08X invalid instruction code\n", *PC, instruction);
			else   printf("invalid instruction code\n");
			exit(1);
		}
		break;
	case BEQ:
		beq(rs, rt, imm, trace_mode, PC, instructions, reg_file);
		break;
	case BNE:
		bne(rs, rt, imm, trace_mode, PC, instructions, reg_file);
		break;
	case ADDI:
		addi(rs, rt, imm, trace_mode, PC, instructions, reg_file);
		break;
	case ORI:
		ori(rs, rt, imm, trace_mode, PC, instructions, reg_file);
		break;
	case LUI:
		lui(rt, imm, trace_mode, PC, instructions, reg_file);
		break;
	default:
		if(trace_mode)  printf("%d: 0x%08X invalid instruction code\n", *PC, instruction);
		else   printf("invalid instruction code\n");
		//break;
		exit(1);
	}
}


// YOU DO NOT NEED TO CHANGE CODE BELOW HERE


// check_arguments is given command-line arguments
// it sets *trace_mode to 0 if -r is specified
//          *trace_mode is set to 1 otherwise
// the filename specified in command-line arguments is returned

char *process_arguments(int argc, char *argv[], int *trace_mode) {
	if (
		argc < 2 ||
		argc > 3 ||
		(argc == 2 && strcmp(argv[1], "-r") == 0) ||
		(argc == 3 && strcmp(argv[1], "-r") != 0)) {
		fprintf(stderr, "Usage: %s [-r] <file>\n", argv[0]);
		exit(1);
	}
	*trace_mode = (argc == 2);
	return argv[argc - 1];
}


// read hexadecimal numbers from filename one per line
// numbers are return in a malloc'ed array
// *n_instructions is set to size of the array

uint32_t *read_instructions(char *filename, int *n_instructions_p) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "%s: '%s'\n", strerror(errno), filename);
		exit(1);
	}

	uint32_t *instructions = NULL;
	int n_instructions = 0;
	char line[MAX_LINE_LENGTH + 1];
	while (fgets(line, sizeof line, f) != NULL) {

		// grow instructions array in steps of INSTRUCTIONS_GROW elements
		if (n_instructions % INSTRUCTIONS_GROW == 0) {
			instructions = instructions_realloc(instructions, n_instructions + INSTRUCTIONS_GROW);
		}

		char *endptr;
		instructions[n_instructions] = strtol(line, &endptr, 16);
		if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
			fprintf(stderr, "%s:line %d: invalid hexadecimal number: %s",
				filename, n_instructions + 1, line);
			exit(1);
		}
		n_instructions++;
	}
	fclose(f);
	*n_instructions_p = n_instructions;
	// shrink instructions array to correct size
	instructions = instructions_realloc(instructions, n_instructions);
	return instructions;
}


// instructions_realloc is wrapper for realloc
// it calls realloc to grow/shrink the instructions array
// to the speicfied size
// it exits if realloc fails
// otherwise it returns the new instructions array
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions) {
	instructions = realloc(instructions, n_instructions * sizeof *instructions);
	if (instructions == NULL) {
		fprintf(stderr, "out of memory");
		exit(1);
	}
	return instructions;
}