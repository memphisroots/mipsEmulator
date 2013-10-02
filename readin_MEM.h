#include<iostream>
#include<fstream>
#include<string>
#include<stdint.h>
#include "Utilities.h"
//#include<ifstream>

using namespace std;


int read_inmem(char file[]){
	 uint16_t buffer = 0;
	 string line;
	 string each;
	 int memspace = 0;
	 
	 //this will change with the argument
     ifstream inFILE (file);
	
	 while(getline(inFILE,line)){
	 	//cout << line << endl;
	 	
	 	for(int i = 0; i < line.size(); i++){
	 		each = line[i] ;
	 		//cout << each <<endl;
	 		if(each == "1"){
	 			buffer = (buffer << 1) + 1;
	 		}
	 		else if(each == "0"){
	 			buffer = (buffer << 1) ;
	 			
	 		}
	 	
	     }
	    //cout << buffer << endl;
	    
	    InstructionMemory[memspace] = buffer;
	 	buffer = 0; 
	 	memspace+= 2;
	 	total_InsCount ++;
	     
	 }
	 
	 
	 

	return 0;
}
