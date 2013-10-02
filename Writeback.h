#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "Utilities.h"

void writeBack()
{
	if(MEMWB_out.RegWrite == 1)
	{
		if(MEMWB_out.MemToReg == 1){
			RegisterFile[MEMWB_out.WriteReg] = MEMWB_out.ReadData;
			WB_out = MEMWB_out.ReadData;
	    }
		else{
		
			RegisterFile[MEMWB_out.WriteReg] = MEMWB_out.ALUout;
            WB_out = MEMWB_out.ALUout;
	    }
	}
}

#endif // !WRITEBACK_H
