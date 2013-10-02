#ifndef inSTRUCT_DECODE_H
#define inSTRUCT_DECODE_H

#include <iostream>
#include <stdint.h>



//----------------------------------------------------------
// UNION storing the different types of instruction sets
//    - Can be defined by the DUMP as raw integer data
//----------------------------------------------------------
union INSTRUCTION{
    //used to initialize the UNION to this type
	uint16_t dump;
	
	//Jump Type inSTRUCTion
	struct J_inst{
	
	    unsigned offset : 12;
		unsigned opcode : 4;
	} J;
	
	//R-Type inSTRUCTion
	struct R_inst{
	
		unsigned rd : 4;
		unsigned rt : 4;
		unsigned rs : 4;
	    unsigned opcode : 4;
	} R;
	
	//I-Type inSTRUCTion
	struct I_inst{
	
	    signed constant : 4;
		unsigned rt : 4;
		unsigned rs : 4;
		unsigned opcode : 4;
	} I;	
};



#endif
