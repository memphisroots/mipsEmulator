#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include "inSTRUCT_Decode.h"

using namespace std;

/************************************************************************/
/*     DEFINING REG NAMES TO THEIR ARRAY LOCATION                       */
/************************************************************************/
#define ZERO 0
#define S0 1
#define S1 2
#define S2 3
#define S3 4
#define T0 5
#define T1 6
#define T2 7
#define FP 8
#define SP 9
#define RA 10
#define A0 11
#define A1 12
#define V0 13
#define V1 14
#define GP 15


/************************************************************************/
/*     Pipeline registers                                               */
/************************************************************************/
struct IFID_struct
{
	int16_t ProgramCounter; //PC + 2
	int16_t Instruction; //16 bit instruction
	
	void flush(){
		ProgramCounter = 0;
        Instruction = 0;
	}

	friend ostream& operator << (ostream &o,const IFID_struct &i)
	{
		o << "=====IFID======" << endl;
		o << "PC: " <<i.ProgramCounter << endl;
		o << "Instruction: " <<i.Instruction << endl;
		o << "===============" << endl;
		return o;
	}
};
struct IDEXE_struct
{
	//control bits
	int MemToReg;
	int ALUSrc;
	int ALU;
	int MemRead;
	int MemWrite;
	int RegWrite;
	
	INSTRUCTION ins;
	
	

	int16_t ReadData1; //RS
	int16_t ReadData2; //RT
	int16_t constant;  //sign extended constant
	int16_t WriteReg;  // register address for WB 

    void flush(){
       MemToReg = 0;
       ALUSrc = 0;
       ALU = 0;
       MemRead = 0;
       MemWrite = 0;
       RegWrite = 0;
       ins.dump = 0;

       ReadData1 = 0;
       ReadData2 = 0;
       constant = 0; 
       WriteReg = 0; 

    }

	friend ostream& operator << (ostream &o,const IDEXE_struct &i)
	{
		cout << "=====IDEXE======" << endl;
		cout << "MemtoReg: " <<i.MemToReg << endl;
		cout << "ALUSrc: " <<i.ALUSrc << endl;
		cout << "ALU: " << i.ALU << endl;
		cout << "MemRead: " << i.MemRead << endl;
		cout << "MemWrite: " << i.MemWrite << endl;
		cout << "RegWrite: " << i.RegWrite << endl;
		cout << "Read Data 1: " << i.ReadData1 << endl;
		cout << "Read Data 2: " << i.ReadData2 << endl;
		cout << "Constant: " << i.constant << endl;
		cout << "Write Register: " << i.WriteReg << endl;
		cout << "===============" << endl;	
		return o;
	}
};
struct EXEMEM_struct
{
	//control bits
	int MemToReg;
	int MemRead;
	int MemWrite;
	int RegWrite; 
	
	INSTRUCTION ins;

	int16_t ALUout;
	int16_t ReadData2; //RT bypassing the ALU
	int16_t WriteReg;  // register address for WB

	 void flush(){
        MemToReg = 0;
        MemRead = 0;
        MemWrite = 0;
        RegWrite = 0;
        
        ins.dump = 0;
        
        ALUout = 0;
        ReadData2 = 0;
        WriteReg = 0; 

	 }

	friend ostream& operator << (ostream &o,const EXEMEM_struct &i)
	{
		cout << "=====EXEMEM======" << endl;
		cout << "MemtoReg: " <<  i.MemToReg << endl;
		cout << "MemRead: " << i.MemRead << endl;
		cout << "MemWrite: " << i.MemWrite << endl;
		cout << "RegWrite: " << i.RegWrite << endl;
		cout << "ALUout: " << i.ALUout << endl;
		cout << "Read Data 2: " << i.ReadData2 << endl;
		cout << "Write Register: " << i.WriteReg << endl;
		cout << "===============" << endl;;
		return o;
	}
};

struct MEMWB_struct
{
	//control bits
	int MemToReg;
	int RegWrite;
	
	INSTRUCTION ins;

	int16_t ReadData;
	int16_t ALUout; //ALU out bypassing the memory
	int16_t WriteReg;  // register address for WB

     void flush(){
        
        MemToReg = 0;
        RegWrite = 0;
        ins.dump = 0;
        
        ReadData = 0;
        ALUout = 0; 
        WriteReg = 0; 

     }

	friend ostream& operator << (ostream &o,const MEMWB_struct &i)
	{
		cout << "=====MEMWB======" << endl;
		cout << "MemtoReg: " << i.MemToReg << endl;
		cout << "RegWrite: " << i.RegWrite << endl;
		cout << "Read Data: " << i.ReadData << endl;
		cout << "ALUout: " << i.ALUout << endl;
		cout << "Write Register: " << i.WriteReg << endl;
		cout << "===============" << endl;;
		return o;
	}
};

//***********************************************************************/
//* 													*/
//***********************************************************************/

/************************************************************************/
/*Variables                                                             */
/************************************************************************/
int clock_s;
int loop;
int16_t total_InsCount = 0;
int16_t DataMemory[65535];
int16_t RegisterFile [16];
int16_t InstructionMemory[65535];
int16_t ProgramCounter;
int16_t WB_out;
IFID_struct IFID_in, IFID_out;
IDEXE_struct IDEXE_in, IDEXE_out;
EXEMEM_struct EXEMEM_in, EXEMEM_out;
MEMWB_struct MEMWB_in, MEMWB_out;

/************************************************************************/
/*Utility Functions                                                     */
/************************************************************************/
void print_binary(uint16_t decimal_num){

	int binary_num = 0;
	int array[8];
	for(int i = 0;i < sizeof(decimal_num);i++){
		binary_num = decimal_num & 1;
		decimal_num = decimal_num >> 1;
		array[(sizeof(decimal_num)-1)-i] = binary_num;
	}
	for(int i = 0;i<8;i++)
		cout<< array[i];

}


void print_mem_and_reg(ostream& dataOut)
{
	
	dataOut << "\tData Memory";
	dataOut << "\t\tRegister File" << endl;
	dataOut <<"   Location ||  Value";
	dataOut <<"\t   Location ||  Value" << endl;
	dataOut << "\t=============";
	dataOut << "\t         ============="<< endl;

	for(int i = 0; i < 25; ++i)
	{
	//	DataMemory[i] = i;
		dataOut << "\t|";
		dataOut << setbase(10) << setw(2) << setfill('0');
		dataOut << i;
		dataOut << " || 0x";
		dataOut << setbase(16) << setw(4) << setfill('0');
		dataOut << DataMemory[i];
		dataOut << "|";
		if(i < 16)
		{
			//RegisterFile[i] = i;
			dataOut << "\t\t|";
			dataOut << setbase(10) << setw(2) << setfill('0');
			dataOut << i;
			dataOut << " || 0x";
			dataOut << setbase(16) << setw(4) << setfill('0');
			dataOut << RegisterFile[i];
			dataOut << "|";
		}
		if(i == 16)
		dataOut << "\t         =============";
		dataOut << endl;
	}
	dataOut << "\t=============\n";
}


void open_inst(){
}

#endif // !UTILITIES_H
