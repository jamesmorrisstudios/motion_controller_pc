#include "serial.h"

HANDLE hComm;



void SerialCon::connect(LPCSTR gszPort){
	
	hComm = CreateFile( gszPort,  
						GENERIC_READ | GENERIC_WRITE, 
						0, 
						0, 
						OPEN_EXISTING,
						FILE_FLAG_OVERLAPPED,
						0);
	if (hComm == INVALID_HANDLE_VALUE){
		// error opening port; abort
	}
		
}
