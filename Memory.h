#ifndef MEMORY_H
#define MEMORY_H

#include "Utilities.h"

void MEMORY()
{
	//transfer control bits
	MEMWB_in.ALUout = EXEMEM_out.ALUout;
	MEMWB_in.MemToReg = EXEMEM_out.MemToReg;
    MEMWB_in.RegWrite = EXEMEM_out.RegWrite;
	//transfer write register address
	MEMWB_in.WriteReg = EXEMEM_out.WriteReg;
	//logic
	if(EXEMEM_out.MemRead == 1)
		MEMWB_in.ReadData = DataMemory[EXEMEM_out.ALUout];//what is address?
	if(EXEMEM_out.MemWrite == 1)
		DataMemory[EXEMEM_out.ALUout] = EXEMEM_out.ReadData2;//what is address?
}



#endif //MEMORY_H
