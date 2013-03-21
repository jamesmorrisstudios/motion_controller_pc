#include "uC.h"
/*
* This function will initially support connecting and communicating with an attached microcontroller via a serial connection
* as that is a simple method over bluetooth. Moving to a Raw Hid method may happen in the future.
*
*
*
*/
RS232 serial;

int comPort;

microController::microController(){}

microController::microController(int com){
	comPort = com;
#ifdef DEBUG
	printf("uC.cpp init microController for com %d\n", comPort);
#endif
	//Open the comPort connection
	//currently a failure is silent TODO
	serial.OpenComport(comPort, DEFAULT_BAUD_RATE);
	//Send the control start signal so the uC will begin sending data
	//serial.SendByte(comPort, CONTROL_START);
	serial.enableDTR(comPort);
}

void microController::updateData(microController::dataStorage * data){
	serial.SendByte(comPort,CONTROL_START);

	unsigned char buffer[PACKET_SIZE] = {0};

	while(serial.PollComport(comPort, buffer, PACKET_SIZE) < 1){}
	//for(int i=0;i<64;i++){
	//	printf("%X ",buffer[i]);
	//}
	//printf("\n\n\n");
	
	//Check if valid transmission (Start and end bytes must be valid)
	if(buffer[0] == PACKET_START_1 && buffer[1] == PACKET_START_2
		&& buffer[PACKET_SIZE - 2] == PACKET_END_1 && buffer[PACKET_SIZE - 1] == PACKET_END_2){

		uint16_t newData;
		//Now walk through starting at buffer index 2 and look for valid data types and copy to the struct
		for(int index=2;index<PACKET_SIZE - 2;index+=3){
			
			newData = (buffer[index+1] << 8) + buffer[index+2];
			switch(buffer[index]){
				case DATA_ANALOG_1:
					data->analog_1= newData;
					break;
				case DATA_ANALOG_2:
					data->analog_2 = newData;
					break;
				case DATA_ANALOG_3:
					data->analog_3 = newData;
					break;
				case DATA_ANALOG_4:
					data->analog_4 = newData;
					break;
				case DATA_ANALOG_5:
					data->analog_5 = newData;
					break;
				case DATA_ANALOG_6:
					data->analog_6 = newData;
					break;
				case DATA_ANALOG_7:
					data->analog_7 = newData;
					break;
				case DATA_ANALOG_8:
					data->analog_8 = newData;
					break;
				case DATA_ANALOG_9:
					data->analog_9 = newData;
					break;
				case DATA_ANALOG_10:
					data->analog_10 = newData;
					break;
				case DATA_ANALOG_11:
					data->analog_11 = newData;
					break;
				case DATA_ANALOG_12:
					data->analog_12 = newData;
					break;
				case DATA_ANALOG_13:
					data->analog_13 = newData;
					break;
				case DATA_ANALOG_14:
					data->analog_14 = newData;
					break;
				case DATA_ANALOG_15:
					data->analog_15 = newData;
					break;
				case DATA_ANALOG_16:
					data->analog_16 = newData;
					break;
				case DATA_DIGITAL_1:
					data->digital_1 = newData;
					break;
				case DATA_DIGITAL_2:
					data->digital_2 = newData;
					break;
				case DATA_DIGITAL_3:
					data->digital_3 = newData;
					break;
				case DATA_DIGITAL_4:
					data->digital_4 = newData;
					break;
				default:
					break;
			}//Switch
		}//buffer loop
	}//Valid check
}
