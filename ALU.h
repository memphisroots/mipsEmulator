#ifndef ALU_H
#define ALU_H

#include<stdio.h>
//#include<iostream>
//include that has the sized integers for expressing binary ints
#include<stdint.h>
#include"Utilities.h"
//using namespace std;

//----Used for unit testing
//int alu_OP = 0b0110;
//int8_t alu_A = 0b00001010;
//int8_t alu_B = 0b00000010;

//int16_t signex = alu_A;

//int8_t  = 0;

#define ADD 0b0000
#define AND 0b0001
#define OR  0b0010
#define NOR 0b0011
#define XOR 0b0100
#define SLT 0b0101
#define SUB 0b0110
//the next one will change
#define ANDI 0b0111

#define SLL  0b1000
#define SRL  0b1001
#define ZE = 0b0000000000000000
#define ONE  = 0b0000000000000001




// @Params:
//    in int ALU_OP 
void funcALU(int ALU_OP, int16_t ALU_A, int16_t ALU_B){
	
	switch(ALU_OP){
		
		case ADD:
			//add
		    EXEMEM_in.ALUout = ALU_A + ALU_B;
			
			break;
		case AND:
			//and
			 EXEMEM_in.ALUout = ALU_A & ALU_B;
			
			break;
		case OR:
			//or
			EXEMEM_in.ALUout = ALU_A | ALU_B;
			break;
		case NOR:
			//nor
			EXEMEM_in.ALUout = ~(ALU_A | ALU_B);
			
			break;
			
		case XOR:
			//xor
			EXEMEM_in.ALUout = ALU_A ^ ALU_B;
			
			break;
			
		case SLT:
			//set less than
			if(ALU_A < ALU_B){
			  EXEMEM_in.ALUout = 0b0000000000000001;
			}
			else{
		      EXEMEM_in.ALUout = 0b0000000000000000;		
			}
		    
			break;
			
		case SUB:
			//SUBTRACT
			EXEMEM_in.ALUout = ALU_A - ALU_B;
			break;
			
		case ANDI:
			//ANDI
			break;
			
		case SLL:
			// Shift left log
				EXEMEM_in.ALUout = ALU_A << ALU_B;
			break;
			
		case SRL:
			//shift right log
				EXEMEM_in.ALUout = ALU_A >> ALU_B;
			break;	
		
		
		
		
		
		default:
			//*******NOTE: there needs to be a program break here
			break;
	}
	
	
	
}


//------Used for unit testing
//int main(){
	
//	int i = 0b0101;
	
//	cout << endl;
	
//    funcALU(alu_OP,alu_A, alu_B);
//    print_binary();
//	cout << endl << (int) ;
//	return 0;
//}


#endif // this is the end of the INCLUDE GUARD ALU_H
