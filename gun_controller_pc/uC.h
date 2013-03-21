#include "standardInclude.h"
#include "RS-232\rs232.h"

#define DEFAULT_BAUD_RATE 115200
#define PACKET_SIZE 64

//Packet and control
#define PACKET_START_1 0x66
#define PACKET_START_2 0x66
#define PACKET_END_1 0x042
#define PACKET_END_2 0x042

#define CONTROL_START 0x05
#define CONTROL_END 0x10

//Data types
#define DATA_ANALOG_1 1
#define DATA_ANALOG_2 2
#define DATA_ANALOG_3 3

#define DATA_ANALOG_4 4
#define DATA_ANALOG_5 5
#define DATA_ANALOG_6 6

#define DATA_ANALOG_7 7
#define DATA_ANALOG_8 8
#define DATA_ANALOG_9 9

#define DATA_ANALOG_10 10 //unused
#define DATA_ANALOG_11 11 //unused
#define DATA_ANALOG_12 12 //unused

#define DATA_ANALOG_13 13
#define DATA_ANALOG_14 14

#define DATA_ANALOG_15 15
#define DATA_ANALOG_16 16

#define DATA_DIGITAL_1 17
#define DATA_DIGITAL_2 18
#define DATA_DIGITAL_3 19 //F is used for analog and is unused here
#define DATA_DIGITAL_4 20

//To add more incoming data put a #define here and increment the number for its ID
//Also add the variable for it into the dataStorage struct




/*
All data to the uC are single byte packets



Data from the uC encoded into 64 byte "packets" this is to facilitate an easy transistion to Raw Hid in the future

The first 16 bits are an packet starting message

The last 16 bits are a packet ending message

The remaining 60 bytes are encoded in the following format

8 bits to define the data coming in

16 bits of data
*/




class microController
{

public:
	struct dataStorage{
		uint16_t analog_1;
		uint16_t analog_2;
		uint16_t analog_3;
		uint16_t analog_4;
		uint16_t analog_5;
		uint16_t analog_6;
		uint16_t analog_7;
		uint16_t analog_8;
		uint16_t analog_9;
		uint16_t analog_10;
		uint16_t analog_11;
		uint16_t analog_12;
		uint16_t analog_13;
		uint16_t analog_14;
		uint16_t analog_15;
		uint16_t analog_16;
		
		uint16_t digital_1;
		uint16_t digital_2;
		uint16_t digital_3;
		uint16_t digital_4;
	};
	microController();

	microController(int comPort);

	void updateData(microController::dataStorage * data);
};