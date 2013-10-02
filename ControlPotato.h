#ifndef CONTROLPOTATO_H
#define CONTROLPOTATO_H

#include"Utilities.h"
//note*****INCLUDE DECODE IN THE FUTURE



//Instantiate ALL CONTROL BITS TO PREVENT GARBAGE
int MemWrite = 0;
int	RegWrite = 0;
int	ALU      = 0b0000;
int	ALUSrc   = 0;
int	MemToReg = 0;
int	Branch   = 0;
int	Jump     = 0;
int	RegDST   = 0;
int MemRead  = 0;
int BEQ      = 0;
int BNE      = 0;

int con_BRANCH;
int con_JUMP;


//FUNCTION FOR OPCODE DECODE
void ControlPotato (int opcode) {
	if (opcode == 0b0000) {  //ADD
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0000;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0001) { //AND
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0001;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0010) { //OR
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0010;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0011) {  //NOR
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0011;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0100) {   //XOR
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0100;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0101) {   //SLT
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0101;
		ALUSrc = 0;
		MemToReg = 0;
		MemRead = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 1;
	} else if (opcode == 0b0110) {  //JUMP
		MemWrite = 0;
		RegWrite = 0;
		MemRead = 0;
		Jump = 1;
	} else if (opcode == 0b0111) {     //BEQ
		MemWrite = 0;
		RegWrite = 0;
		ALU = 0b0110;
		ALUSrc = 1;
		Branch = 1;
		BEQ = 1;
		Jump = 0;
		MemRead = 0;
	} else if (opcode == 0b1000) {   //ADDI
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0000;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0; 
		MemRead = 0;
	} else if (opcode == 0b1001) {   //BNE
		MemWrite = 0;
		RegWrite = 0;
		ALU = 0b0110;
		ALUSrc = 1;
		Branch = 1;
		Jump = 0;
		BNE  = 1;
		MemRead = 0;
	} else if (opcode == 0b1010) {  //ANDI
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0001;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
		MemRead = 0;
	} else if (opcode == 0b1011) {   //SLTI
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b0101;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
		MemRead = 0;
	} else if (opcode == 0b1100) {    //LW
		MemWrite = 0;
		MemRead = 1;
		RegWrite = 1;
		ALU = 0b0000;
		ALUSrc = 1;
		MemToReg = 1;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
	} else if (opcode == 0b1101) {   //SW
		MemWrite = 1;
		RegWrite = 0;
		ALU = 0b0000;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
		MemRead = 0;
	} else if (opcode == 0b1110) {    //SLL
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b1000;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
		MemRead = 0;
	} else if (opcode == 0b1111) {     //SRL
		MemWrite = 0;
		RegWrite = 1;
		ALU = 0b1001;
		ALUSrc = 1;
		MemToReg = 0;
		Branch = 0;
		Jump = 0;
		RegDST = 0;
		MemRead = 0;
	}
	
	
	//Passed forward
	IDEXE_in.ALU = ALU;
	IDEXE_in.RegWrite = RegWrite;
	IDEXE_in.ALUSrc = ALUSrc;
	IDEXE_in.MemWrite = MemWrite;
	IDEXE_in.MemRead = MemRead;
	IDEXE_in.MemToReg = MemToReg;

}

#endif  //end of INCLUDE PROTECT
