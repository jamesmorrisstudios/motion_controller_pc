#include "gun_controller_pc.h"

/*
Entry point to the application
This will eventually include adding some abilities to change profiles and some settings
*/

keyMouse control;

int _tmain(int argc, _TCHAR* argv[])
{
	while(1){
		//
		//Calls the keyboard and mouse handlers update function
		//
		control.update();
		//Currently sleep is in here to prevent the application from flooding sendInput with updates
		//Experimental testing showed that flooding it with data resulted in stuttery mouse movements.
		//TODO provide an option in settings to define a target update rate to compensate for different uC speeds
		Sleep(10);
	}
	return 0;
}
