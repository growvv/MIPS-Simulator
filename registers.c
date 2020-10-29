#include "registers.h"

struct reg reg_file[32];

void init_reg_file()
{
	// Initialises the register file. This function should be called 
	// before the first time the registerfile is accessed.	


	strcpy(reg_file[0].name, "zero");
	strcpy(reg_file[1].name, "at");
	strcpy(reg_file[2].name, "v0");
	strcpy(reg_file[3].name, "v1");
	strcpy(reg_file[4].name, "a0");
	strcpy(reg_file[5].name, "a1");
	strcpy(reg_file[6].name, "a2");
	strcpy(reg_file[7].name, "a3");
	strcpy(reg_file[8].name, "t0");
	strcpy(reg_file[9].name, "t1");
	strcpy(reg_file[10].name, "t2");
	strcpy(reg_file[11].name, "t3");
	strcpy(reg_file[11].name, "t3");
	strcpy(reg_file[12].name, "t4");
	strcpy(reg_file[13].name, "t5");
	strcpy(reg_file[14].name, "t6");
	strcpy(reg_file[15].name, "t7");
	strcpy(reg_file[16].name, "s0");
	strcpy(reg_file[17].name, "s1");
	strcpy(reg_file[18].name, "s2");
	strcpy(reg_file[19].name, "s3");
	strcpy(reg_file[20].name, "s4");
	strcpy(reg_file[21].name, "s5");
	strcpy(reg_file[22].name, "s6");
	strcpy(reg_file[23].name, "s7");
	strcpy(reg_file[24].name, "t8");
	strcpy(reg_file[25].name, "t9");
	strcpy(reg_file[26].name, "k0");
	strcpy(reg_file[27].name, "k1");
	strcpy(reg_file[28].name, "gp");
	strcpy(reg_file[29].name, "sp");
	strcpy(reg_file[30].name, "fp");
	strcpy(reg_file[31].name, "ra");

	return;
}

int reg_name2num(char* name)
{
	int i = 0;
	for (; i < 32; i++)
	{
		if (!strcpy(reg_file[i].name, name))
			break;
	}
	if (i < 32)  return i;
	else
	{
		printf("not found register\n");
		exit(1);
	}
}