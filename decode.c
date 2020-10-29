#include "decode.h"
#include "operations.h"

int16_t get_complement(int16_t imm)
{
	if (imm < 0)
		imm = (~(-imm)) + 1;   
	return imm;
}

void execute_single(uint32_t instruction, int trace_mode)
{
	int op = instruction >> 26;
	int rs = (instruction >> 21) & 0x1F;
	int rt = (instruction >> 16) & 0x1F;
	int rd = (instruction >> 11) & 0x1F;
	int shamt = (instruction >> 6) & 0x1F;
	int funct = instruction & 0x3F;

	int imm = get_complement(instruction & 0xFFFF);

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
			add(rd, rs, rt);
			break;
		case SUB:
			sub(rd, rs, rt);
			break;
		case SLT:
			slt(rd, rs, rt);
			break;
		case SYSCALL:
			if (rs == 0 && rt == 0 && rd == 0 && shamt == 0)
				syscall();
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
			mul(rd, rs, rt);
		else
			printf("invalid instruction code\n");
		break;
	case BEQ:
		beq(rs, rt, imm);
		break;
	case BNE:
		bne(rs, rt, imm);
		break;
	case ADDI:
		addi(rs, rt, imm);
		break;
	case ORI:
		ori(rs, rt, imm);
		break;
	case LUI:
		lui(rt, imm);
		break;
	default:
		printf("invalid instruction code\n");
		break;
	}
}