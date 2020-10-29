#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

#include<stdint.h>

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

void encode(uint32_t instruction);
void decode(uint32_t instructions);


#endif		//End of file