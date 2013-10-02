#include <iostream>
#include "ALU.h"
#include "Fetch.h"
#include "Writeback.h"
#include "Utilities.h"
#include "EXE.h"
#include "Memory.h"
#include "DECODE.h"
#include "readin_MEM.h"
#include <stdint.h>
#include <string>
#include<fstream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char *argv[]) {
	
//	ofstream log_mem (argv[2]); 
//	if(argc != 3){
	  //change for linux environment
	  ofstream log_mem ("log.txt");
	  
//-	}
	
    
	
	int nop = 0;
	read_inmem(argv[1]);
	
	

    RegisterFile[0] = 0x0000;
	RegisterFile[1] = 0x0040;  // $S0  - ($V0)
	RegisterFile[2] = 0x1010;  // $S1  - ($V1)
	RegisterFile[3] = 0x000f;  // $S1  - ($V2)
	RegisterFile[4] = 0x00f0;  // $S3  - ($V3)
	
	RegisterFile[5] = 0x0000;   // $T0  - ($T0)
	
	RegisterFile[11] = 0x0010;  // $a0  - ($a0)
	RegisterFile[12] = 0x0005;  // $a1  - ($a1)
	
	DataMemory[RegisterFile[11]]   =  0x0101;
	DataMemory[RegisterFile[11]+2] =  0x0110;
	DataMemory[RegisterFile[11]+4] =  0x0011;
	DataMemory[RegisterFile[11]+6] =  0x00f0;
	DataMemory[RegisterFile[11]+8] =  0x00ff;
	
	
	while(ProgramCounter < total_InsCount || nop < 4){
		
	     if(ProgramCounter == 0){
	       loop++;
		   print_mem_and_reg(log_mem);
		  // cout << "==========================" << endl;
		   log_mem << "==========================" << endl;  
		   log_mem << "Loop : " << loop << "  |  :" << setbase(10) << clock_s	 << endl;
		   log_mem << "==========================" << endl;  
		 }
		
		//log_mem << ProgramCounter << endl;
		 
	   //FLUSH
	   IFID_out.flush();
	   IFID_in = IFID_out;
	   
	   IDEXE_out.flush();
	   IDEXE_in = IDEXE_out;
	   
	   EXEMEM_out.flush();
	   EXEMEM_in = EXEMEM_out;
	   
	   MEMWB_out.flush();
	   MEMWB_in = MEMWB_out;
	   //-------------------------
	   
	   
	   FETCH();
	   IFID_out = IFID_in;
	   clock_s++;
	   
	   DECODE();
	   
	   IFID_out.flush();
	   IFID_in = IFID_out;
	   IDEXE_out = IDEXE_in;
	   clock_s++;
	   
	   EXE();
	   
	   IDEXE_out.flush();
	   IDEXE_in = IDEXE_out;
	   EXEMEM_out = EXEMEM_in;
	   clock_s++;
	   
	   MEMORY(); 
	
	   EXEMEM_out.flush();
	   EXEMEM_in = EXEMEM_out;
	   MEMWB_out = MEMWB_in;
	   clock_s++;
	    
	   writeBack(); 
	   
	   MEMWB_out.flush();
	   MEMWB_in = MEMWB_out;
	   clock_s++;
	    
	  if(ProgramCounter > total_InsCount*2){
	  	nop++;
	  }
    }

//OLD WAY
//   FETCH();
//	IFID_out = IFID_in;	
//	DECODE();
//	IDEXE_out = IDEXE_in;
//	EXE();
//	EXEMEM_out = EXEMEM_in;
//	MEMORY();
//	MEMWB_out = MEMWB_in;
//	writeBack();
//END OLD WAY	
    print_mem_and_reg(log_mem);
    print_mem_and_reg(cout);
    //cout << InstructionMemory[4] << endl;
    
    
	return 0;
}



