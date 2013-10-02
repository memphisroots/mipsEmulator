#ifndef EXE_H
#define EXE_H

#include "Utilities.h"
#include <stdint.h>

int16_t alu_A, alu_B;
int forward_mux_a = 0;
int forward_mux_b = 0;

void ForwardingHaz();

void EXE(){
// PUSH FORWARD ALL PERTINANT DATA AND THE CONTROL BITS FROM EXEMEM TO OUT BUFFER FOR IDEXE
EXEMEM_in.MemRead = IDEXE_out.MemRead;
EXEMEM_in.MemWrite = IDEXE_out.MemWrite;
EXEMEM_in.MemToReg = IDEXE_out.MemToReg;
EXEMEM_in.RegWrite = IDEXE_out.RegWrite;
EXEMEM_in.ReadData2 = IDEXE_out.ReadData2;
EXEMEM_in.RegWrite = IDEXE_out.RegWrite;
EXEMEM_in.WriteReg = IDEXE_out.WriteReg;	
	
	
forward_mux_a = 0;
forward_mux_b = 0;

ForwardingHaz();	

switch(forward_mux_a){
	
	case 0:
		alu_A = IDEXE_out.ReadData1;
		break;
	case 1:
		alu_A = WB_out;
		break;
		
	case 2:
		alu_A = EXEMEM_out.ALUout;
		break;
		
	default:
		break;
	
}

switch(forward_mux_b){
	
	case 0:
		alu_B = IDEXE_out.ReadData2;
		EXEMEM_in.ReadData2 = alu_B;
		break;
		
	case 1:
		alu_B = WB_out;
		EXEMEM_in.ReadData2 = alu_B;
		break;
		
	case 2:
		alu_B = EXEMEM_out.ALUout;
		EXEMEM_in.ReadData2 = alu_B;
		break;
		
	default:
		break;
	
	
	
}
	
int OP = IDEXE_out.ALU;
//ALU TOP INPUT CALLED FROM IDEXE BUFFER REGISTER



//THIS CHECKS THE MUX ALUSRC CONTROL BIT
// SETS THE ALU BOTTOM INPUT FROM THE APPROPRIATE INPUT!!!
if(IDEXE_out.ALUSrc == 1){
	alu_B = IDEXE_out.constant;
}


//RUN FUNCTION FROM ALU.H
funcALU(OP,alu_A,alu_B);


}

void ForwardingHaz(){
	
	//****************************************/
	//*  EXE HAZARD (totally not from slide
	//****************************************/	
	if((EXEMEM_out.RegWrite) && (EXEMEM_out.WriteReg != 0) && (EXEMEM_out.WriteReg==IDEXE_out.ins.I.rs)){
		 forward_mux_a = 2;
		 cout << "(.)(.)(.)!!!!Forward Nigga!!!!(.)(.)(.)(.)(.)(.)(.)(.)(.) aq" << endl;
	}
	if((EXEMEM_out.RegWrite) && (EXEMEM_out.WriteReg != 0) && (EXEMEM_out.WriteReg==IDEXE_out.ins.I.rt)){
	     forward_mux_b = 2;
	     cout << "(.)(.)(.)!!!!Forward Nigga!!!!(.)(.)(.)(.)(.)(.)(.)(.)(.) bq" << endl;
	}
	
	//****************************************/
	//*  MEM HAZARD (totally not from slide
	//****************************************/	

   if(forward_mux_a !=2){
	if(((MEMWB_out.RegWrite) &&  (MEMWB_out.WriteReg != 0)  &&  (MEMWB_out.WriteReg == IDEXE_out.ins.I.rs))){
		forward_mux_a = 1;
		cout << "(.)(.)(.)!!!!Forward Nigga!!!!(.)(.)(.)(.)(.)(.)(.)(.)(.) az" << endl;
	}
   }
//&& !((EXEMEM_out.RegWrite) && (EXEMEM_out.WriteReg != 0) && (EXEMEM_out.WriteReg==IDEXE_out.ins.I.rs))	   
	

   if(forward_mux_b !=2){
   	if(((MEMWB_out.RegWrite) &&  (MEMWB_out.WriteReg != 0)  &&  (MEMWB_out.WriteReg == IDEXE_out.ins.I.rt))){
		forward_mux_b = 1;
		cout << "(.)(.)(.)!!!!Forward Nigga!!!!(.)(.)(.)(.)(.)(.)(.)(.)(.) bj" << endl;
	}
   }

	// && !((EXEMEM_out.RegWrite) && (EXEMEM_out.WriteReg != 0) && (EXEMEM_out.WriteReg==IDEXE_out.ins.I.rt))


}



#endif  //END OF ICLUDE PROTECT EXE_H
