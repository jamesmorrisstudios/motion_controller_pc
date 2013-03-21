#include "standardInclude.h"
#include "controlMap.h"

/*
 This class makes use of the uC data structure and the controlMap to send keyboard key presses


*/

//Since there is no windows define for these i added some in the
//section that is oem specific
//
//The rest of the key codes are available on msdn
//
//These are used in the buildLookupTable function
//
//http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
//
#define VK_CUSTOM_SCROLLUP 0xE9
#define VK_CUSTOM_SCROLLDOWN 0xEA

class keyMouse
{
public:
	keyMouse();
	void update();
	void applyKeys();

private:
	void moveMouse(int x, int y);
	void pressKey(INPUT &event, SHORT key);
	void releaseKey(INPUT &event, SHORT key);
	void pressMouse(INPUT &event, SHORT key);
	void releaseMouse(INPUT &event, SHORT key);
	void buildLookupTable();
	void processMotionPress(std::string motion);
	void processMotionRelease(std::string motion);
};