#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED

struct reg
{
	char name[4];			// Stores names like $v0, $ra...
	int val;                // 
};

extern struct reg reg_file[32];
extern int PC;

void init_reg_file();   
int reg_name2num(char* name);  // from name to number

#endif		//End of file