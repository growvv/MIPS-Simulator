#include "decode.h"
#include "operations.h"

void execute_single(uint32_t instruction, int trace_mode)
{
	int op = instruction >> 26;
	int rs = (instruction >> 21) & 0x1F;
	int rt = (instruction >> 16) & 0x1F;
	int rd = (instruction >> 11) & 0x1F;
	int shamt = (instruction >> 6) & 0x1F;
	int funct = instruction & 0x3F;

	int imm = instruction & 0xFFFF;

	switch(op)     // according to opcode and funct
	{
	case 0:
		if (shamt != 0)
		{
			printf("invalid instruction code\n");
			break;
		}
		switch (funct)
		{
		case ADD:
			if(trace_mode)  printf("%d: 0x%08X add $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			add(rd, rs, rt);
			if(trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SUB:
			if(trace_mode)  printf("%d: 0x%08X sub $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			sub(rd, rs, rt);
			if(trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SLT:
			if(trace_mode)  printf("%d: 0x%08X add $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			slt(rd, rs, rt);
			if(trace_mode)  printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SYSCALL:
			if (rs == 0 && rt == 0 && rd == 0 && shamt == 0)
			{
				if(trace_mode)  printf("%d: 0x%08X syscall\n", PC, instruction);
				if(trace_mode)  printf(">>> syscall %d\n", reg_file[2].val);
				syscall(trace_mode);
			}
			else
				printf("invalid instruction code\n");
			break;
		default:
			printf("invalid instruction code\n");
			break;
		}
		break;
	case MUL_op:
		if (shamt == 0 && funct == MUL_funct)
		{
			if(trace_mode) printf("%d: 0x%08X mul $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			mul(rd, rs, rt);
			if(trace_mode) printf(">>> $%d = %d\n", rd, reg_file[rd].val);
		}
		else
			printf("invalid instruction code\n");
		break;
	case BEQ:
		if(trace_mode)  printf("%d: 0x%08X beq $%d, $%d, %d\n", PC, instruction, rs, rt, imm);
		beq(rs, rt, imm);
		break;
	case BNE:
		if(trace_mode)  printf("%d: 0x%08X bne $%d, $%d, %d\n", PC, instruction, rs, rt, imm);
		bne(rs, rt, imm);
		break;
	case ADDI:
		if(trace_mode)  printf("%d: 0x%08X addi $%d, $%d, $%d\n", PC, instruction, rt, rs, imm);
		addi(rs, rt, imm);
		if(trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	case ORI:
		if(trace_mode)  printf("%d: 0x%08X ori $%d, $%d, %d\n", PC, instruction, rt, rs, imm);
		ori(rs, rt, imm);
		if(trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	case LUI:
		if(trace_mode)  printf("%d: 0x%08X lui $%d, $%d\n", PC, instruction, rt, imm);
		lui(rt, imm);
		if(trace_mode)  printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	default:
		printf("invalid instruction code\n");
		break;
	}
}