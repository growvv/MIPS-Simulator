#include "decode.h"
#include "operations.h"

void execute_single(uint32_t instruction)
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
			printf("%d: 0x%08X add $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			add(rd, rs, rt);
			printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SUB:
			printf("%d: 0x%08X sub $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			sub(rd, rs, rt);
			printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SLT:
			printf("%d: 0x%08X add $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			slt(rd, rs, rt);
			printf(">>> $%d = %d\n", rd, reg_file[rd].val);
			break;
		case SYSCALL:
			if (rs == 0 && rt == 0 && rd == 0 && shamt == 0)
			{
				printf("%d: 0x%08X syscall\n", PC, instruction);
				printf(">>> syscall %d\n", reg_file[2].val);
				syscall();
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
			printf("%d: 0x%08X mul $%d, $%d, $%d\n", PC, instruction, rd, rs, rt);
			mul(rd, rs, rt);
			printf(">>> $%d = %d\n", rd, reg_file[rd].val);
		}
		else
			printf("invalid instruction code\n");
		break;
	case BEQ:
		printf("%d: 0x%08X beq $%d, $%d, %d\n", PC, instruction, rs, rt, imm);
		beq(rs, rt, imm);
		//printf(">>> $%d = %d\n", rd, reg_file[rd].val);
		break;
	case BNE:
		printf("%d: 0x%08X bne $%d, $%d, %d\n", PC, instruction, rs, rt, imm);
		bne(rs, rt, imm);
		break;
	case ADDI:
		printf("%d: 0x%08X addi $%d, $%d, $%d\n", PC, instruction, rt, rs, imm);
		addi(rs, rt, imm);
		printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	case ORI:
		printf("%d: 0x%08X ori $%d, $%d, %d\n", PC, instruction, rt, rs, imm);
		ori(rs, rt, imm);
		printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	case LUI:
		printf("%d: 0x%08X ori $%d, $%d\n", PC, instruction, rt, imm);
		lui(rt, imm);
		printf(">>> $%d = %d\n", rt, reg_file[rt].val);
		break;
	default:
		printf("invalid instruction code\n");
		break;
	}
}