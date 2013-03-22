#include "motionProcess.h"
#include <time.h>  

motionProcess::motionProcess(){}

#define gyro_end_point 20
double mouse_sensitivity_x = 400.0;
double mouse_sensitivity_y = 400.0;
double mouse_move_hist_y;
double mouse_move_hist_x;

int count = 0;
time_t startTime;
time_t endTime;

double start;
double end;

void motionProcess::processInput(motionData * data, int *x, int *y){
	mouse_move_vertical(y, data);
	mouse_move_horizontal(x, data);
	

	//if(data->motionDisable == true){
	//	printf("motion disabled...\n");
		//x = 0;
		//y = 0;
//	}

//	if(count == 0){
	//	startTime = time(0);
//		printf("Time start %d\n",startTime);
//	}

//	count++;

//	if(count == 10000){
//		endTime = time(0);
		//double seconds = difftime(endTime,startTime);
		//printf("diftime %d\n",seconds);

//		endTime = time(0);
//		printf("Time end   %d\n",endTime);

//	}

}

//
//This was copied from my previous version with the uC and may not be optimal here
//
void motionProcess::mouse_move_vertical(int *mouse_y, motionData * data){
	double mouse_move_y;
	double temp;
	//look up (gyro value higher then middle)
	//look down (gyro value lower then middle)
	//if(data->gyro_4_y.value > gyro_end_point && data->gyro_4_y.value < 2*data->gyro_4_y.mid - gyro_end_point)
	//{	//use precise gyro for low movement
	//	mouse_move_y = -((data->gyro_4_y.value - data->gyro_4_y.mid)/(4.0 * mouse_sensitivity_y));
	//}else
	//{
		mouse_move_y = -((data->gyro_y.value - data->gyro_y.mid)/mouse_sensitivity_y);
	//}
	mouse_move_y += mouse_move_hist_y; //add in what was left last time
	mouse_move_hist_y = modf(mouse_move_y, &temp); //remember any partial movement
	if(mouse_move_y >= 0)
	{
		mouse_move_hist_y += max(mouse_move_y - 126, 0);
	}else
	{
		mouse_move_hist_y += min(mouse_move_y + 126, 0);
	}
	mouse_move_y = min(max(temp, -126), 126); //constrain mouse value from -126 -> 126
	*mouse_y = (int)mouse_move_y;
}

//
//This was copied from my previous version with the uC and may not be optimal here
//
void motionProcess::mouse_move_horizontal(int *mouse_x, motionData * data){
	double mouse_move_x;
	double temp;
	//look left (gyro value higher then middle)
	//look right (gyro value lower then middle)
	//if(data->gyro_4_x.value > gyro_end_point && data->gyro_4_x.value < 2*data->gyro_4_x.mid - gyro_end_point)
	//{	//use precise gyro for low movement
		//mouse_move_x = -((data->gyro_4_x.value - data->gyro_4_x.mid)/(4.0 * (mouse_sensitivity_x)));
	//}else
	//{
		mouse_move_x = -((data->gyro_x.value - data->gyro_x.mid)/(mouse_sensitivity_x));
	//}
	mouse_move_x += mouse_move_hist_x; //add in what was left last time
	mouse_move_hist_x = modf (mouse_move_x , &temp); //remember any partial movement
	if(mouse_move_x >= 0)
	{
		mouse_move_hist_x += max(mouse_move_x - 126, 0);
	}else
	{
		mouse_move_hist_x += min(mouse_move_x + 126, 0);
	}
	mouse_move_x = min(max(temp, -126), 126); //constrain mouse value from -126 -> 126
	*mouse_x = (int)mouse_move_x;
}