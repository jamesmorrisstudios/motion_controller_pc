#include "standardInclude.h"

class motionProcess
{

public:
	struct analogValues{
		std::string name;
		uint16_t value;
		int min;
		int max;
		int mid;
		int deadzone;
		int index;
	};

	struct motionData{
		analogValues gyro_x;
		analogValues gyro_y;
		analogValues gyro_z;

		//These are used when the gyro has an amplified output that is 4x the standard outputs
		analogValues gyro_4_x;
		analogValues gyro_4_y;
		analogValues gyro_4_z;

		//Support is coming soon
		analogValues accel_x;
		analogValues accel_y;
		analogValues accel_z;

		//Not yet supported at all
		analogValues mag_x;
		analogValues mag_y;
		analogValues mag_z;

		bool motionDisable;
	};

	motionProcess();
	void processInput(motionData * data, int *x, int *y);

private:
	void mouse_move_vertical(int * mouse_y, motionData * data);
	void mouse_move_horizontal(int * mouse_x, motionData * data);
};