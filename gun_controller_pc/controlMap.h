#include "standardInclude.h"
#include "utilities.h"
#include "uC.h"
#include "motionProcess.h"

class controlMap
{

public:
	controlMap();

	struct virtualButton{
		std::string input;
		std::string output;
		int deadzone;
		std::string trigger;
	};

	void getData(std::vector<std::string> * buttons, motionProcess::motionData * moData);
	void initSettings();

private:
	void copyMotionData(motionProcess::motionData * moData);
	void readAnalogSetting();
	void getMapping();
	void translateButtons(std::vector<std::string> * buttons);
	void translateVirtualButtons(std::vector<std::string> * buttons);
	void readSettings();
};