#ifndef FETCH_H
#define FETCH_H

void FETCH() {
	IFID_in.ProgramCounter = ProgramCounter+2;
	IFID_in.Instruction = InstructionMemory[ProgramCounter];
}

#endif // !FETCH_H
