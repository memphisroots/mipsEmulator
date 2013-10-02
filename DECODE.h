#ifndef DECODE_H
#define DECODE_H

#include "ControlPotato.h"
#include "inSTRUCT_Decode.h"
#include <stdint.h>

INSTRUCTION i;
bool stall;
void hazard_detection();

void DECODE(){
   // VARS==========
    // output of jump mux
   uint16_t jump_mux_out; 
    //output of branch mux
   uint16_t branch_mux_out;
    // used for adding constant from I type to program counter 
   uint16_t branch_mux_1;
   //constant from I type
   int16_t CONSTANT;
   stall = false;
   
   //used as the second bit in the AND for branching
   int comparator = 0;
   
   INSTRUCTION jump;
   
   // END VARS =====

   i.dump = IFID_out.Instruction;
   
   //constant in I type
   CONSTANT = i.I.constant;
   
   
   // TOTALLY SET THE CONSTANT INTO THE IDEXE reg
   IDEXE_in.constant = CONSTANT;
   
   
   //FOR USE IN THE BRANCH / JUMP INSTRUCTION THE CONSTANT NEEDS TO BE SHIFTED left 1
   CONSTANT = CONSTANT << 1;


 
   
   //---------------------------------------------------------------------------------------
   //  1) Get opcode from instruction ( can be from any type...arbitrarily chose I)
   //  2) Use opCode with ControlPotato.h to set the control bits
   //---------------------------------------------------------------------------------------
   int opCode = i.I.opcode;
   ControlPotato(opCode);

   //--------------------------------------------------------------------------------------------------------------------
   //
   //  REGDST = 1 : Must be R Type Instruction == do everything the R -type would need | set r-type related data
   //  JUMP   = 1 : Must be Jump Type Instruction, use the jump offset |  Comes from Control Potatoe
   //  REGDST = 0 : Must be I Type Instruction == do everything the R -type would need | set r-type related data
   //
   //--------------------------------------------------------------------------------------------------------------------
   
   //==================================
   // MUX THAT USES RegDST
   //==================================
   
   //mux for I-Type | R-Type

   if(RegDST == 1){
    //R-Type INstructions
    IDEXE_in.ReadData1 = RegisterFile[i.R.rs];
    IDEXE_in.ReadData2 = RegisterFile[i.R.rt];
    IDEXE_in.WriteReg = i.R.rd;
    
   }
   else{
   	// I-Type
   	IDEXE_in.ReadData1 = RegisterFile[i.R.rs];
    IDEXE_in.ReadData2 = RegisterFile[i.R.rt];
    IDEXE_in.WriteReg = i.R.rt;
   	
   }
   //===================================
   // END OF Reg DST
   //===================================
   

   if(Jump == 1){
    // Jump Type
    
	jump.J.offset = i.J.offset << 1;
	//this gets the 4 left most bits from the program counter : so spaketh the notes
	jump.J.opcode = IFID_out.ProgramCounter  >> 12;
    
   }
   
   if(IDEXE_in.ReadData1 == IDEXE_in.ReadData2){
   	// test the comparator coming out of the reg file
   	 comparator = 1;
   }


    //=========================
    //  THE TOP PORTION OF DECODE
    //=========================
   //MUX FOR JUMP
   // IF JUMP is 1 then the code for jump will execute, and not do the code for branch
   // ELSE  only run the pertinant code for branch
   if(Jump){
   	  jump_mux_out = jump.dump;
   }
   else
   {
   	   
   	  // Code for choosing between BNE and BEQ
   	   //int bne_to_or = (BNE &&(!comparator));
   	   //int beq_to_or = (BEQ &&  comparator );
   	   //int branch_or_out = (bne_to_or || beq_to_or);
   	  int b_mux_set_bit = 0;
   	  
   	  if(Branch){
   	  	b_mux_set_bit = ( (BNE && (!comparator)) || (BEQ &&  comparator ) );
   	  }
   	  // END of BEQ BNE CODE
   	  
	    // MUX FOR BRANCH
      if(b_mux_set_bit){
      	branch_mux_1 = CONSTANT + IFID_out.ProgramCounter;
   	    branch_mux_out = branch_mux_1;
      }
      else{
      	//program stuff in utilities
   	    branch_mux_out = IFID_out.ProgramCounter;
      }
      
      jump_mux_out = branch_mux_out;
   }
   
   //Passing instruction forward 
   IDEXE_in.ins.dump = i.dump;
   //sets the program counter to the appropriate number from all of that junk
   
   //hazard_detection();
   if(stall)
   {
   		ProgramCounter = ProgramCounter;
   }
   else
   		ProgramCounter = jump_mux_out;
   //===========================
   // END TOP PART OF DECODE
   //===========================
   
   
  
}

void hazard_detection()
{
	
	if(IDEXE_out.MemRead && ((IDEXE_out.ins.I.rt == i.R.rs)
						 ||  (IDEXE_out.ins.I.rt == i.R.rt)))
	{
		stall = true;
		IDEXE_in.ALU       = 0;
		IDEXE_in.ALUSrc    = 0;
		IDEXE_in.constant  = 0;
		IDEXE_in.MemRead   = 0;
		IDEXE_in.MemWrite  = 0;
		IDEXE_in.ReadData1 = 0;
		IDEXE_in.ReadData2 = 0;
		IDEXE_in.RegWrite  = 0;
		IDEXE_in.WriteReg  = 0;
		IDEXE_in.ins.dump  = 0;
		cout << "HAZARD DETECTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}
	else
		stall = false;
		
   if(Branch && ((IDEXE_out.ins.I.rt == i.R.rs)
						 ||  (IDEXE_out.ins.I.rt == i.R.rt)))
	{
		//ProgramCounter -= 2;
		stall = true;
		IDEXE_in.ALU       = 0;
		IDEXE_in.ALUSrc    = 0;
		IDEXE_in.constant  = 0;
		IDEXE_in.MemRead   = 0;
		IDEXE_in.MemWrite  = 0;
		IDEXE_in.ReadData1 = 0;
		IDEXE_in.ReadData2 = 0;
		IDEXE_in.RegWrite  = 0;
		IDEXE_in.WriteReg  = 0;
		IDEXE_in.ins.dump  = 0;
		cout << "HAZARD DETECTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}
	else
		stall = false;
}



#endif  // ends the INCLUDE PROTECTION
