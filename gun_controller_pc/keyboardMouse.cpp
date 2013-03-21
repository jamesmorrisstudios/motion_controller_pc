#include "keyboardMouse.h"

controlMap map;
motionProcess motion;

std::vector<std::string> buttons;
std::vector<std::string> buttonsOld;

typedef std::map<std::string, SHORT> buttonMap;
buttonMap bmap;

bool firstRun = true;

motionProcess::motionData moData;

int counter = 0;

keyMouse::keyMouse(){}

void keyMouse::update(){
	if(firstRun){
		buildLookupTable();
		firstRun = false;
	}
	//Retrieve the button and motion data from the uC
	map.getData(&buttons, &moData);
	//Press or release any buttons given by the buttons vector
	//This includes any "virtual" buttons from analog values
	applyKeys();
	int x;
	int y;
	//Process the motion input for moving the mouse
	motion.processInput(&moData, &x, &y);
	//Apply the mouse movement if enabled
	if(!moData.motionDisable){
		moveMouse(x,y);
	}
}

void keyMouse::applyKeys(){
	INPUT eventPress = {0};
	INPUT eventRelease = {0};
	bool send = false;

	//Check if there is anything new to press
	for(std::vector<std::string>::size_type i = 0; i != buttons.size(); i++) {
		//if in buttons and not in buttonsOld press it
		if(!(std::find(buttonsOld.begin(), buttonsOld.end(), buttons[i]) != buttonsOld.end())){
			// buttonsOld does not contain buttons[i] so press the button
			if(buttons[i].find("KEY") != std::string::npos){
				pressKey(eventPress, bmap[buttons[i]]);
				send = true;
			}else if(buttons[i].find("MOUSE") != std::string::npos){
				pressMouse(eventPress, bmap[buttons[i]]);
				send = true;
			}else if(buttons[i].find("MOTION") != std::string::npos){
				send = false;
				processMotionPress(buttons[i]);
			}
			if(send == true){
				SendInput( 1, &eventPress, sizeof( eventPress ) );
			}
		}
	}

	//Check if anything that was pressed last time is now unpressed
	for(std::vector<std::string>::size_type i = 0; i != buttonsOld.size(); i++) {
		//if in buttonsOld and not in buttons release it
		if( !(std::find(buttons.begin(), buttons.end(), buttonsOld[i]) != buttons.end())) {
			// buttons does not contain buttonsOld[i] so release the button press
			if(buttonsOld[i].find("KEY") != std::string::npos){
				releaseKey(eventRelease, bmap[buttonsOld[i]]);
				send = true;
			//	std::cout << " ReleaseKey: " << buttonsOld[i] << "\n";
			}else if(buttonsOld[i].find("MOUSE") != std::string::npos){
				releaseMouse(eventRelease, bmap[buttonsOld[i]]);
				send = true;
				//std::cout << " ReleaseMouse: " << buttonsOld[i] << "\n";
			}else if(buttonsOld[i].find("MOTION") != std::string::npos){
				send = false;
				processMotionRelease(buttonsOld[i]);
			}
			if(send == true){
				SendInput( 1, &eventRelease, sizeof( eventRelease ) );
			}
		}
	}
	buttonsOld = buttons;
	//clear the vector
	buttons.clear();
}

void keyMouse::moveMouse(int x, int y){
	INPUT Input={0};
    Input.type = INPUT_MOUSE;
    Input.mi.dx = (LONG)x;
    Input.mi.dy = (LONG)y;
    // set move cursor
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_MOVE_NOCOALESCE;
    SendInput(1,&Input,sizeof(INPUT));
}

void keyMouse::processMotionPress(std::string motion){
	if(motion == "MOTION_DISABLE"){
		moData.motionDisable = true;
	}
}

void keyMouse::processMotionRelease(std::string motion){
	if(motion == "MOTION_DISABLE"){
		moData.motionDisable = false;
	}
}

void keyMouse::pressKey(INPUT &event, SHORT key){
	const UINT mappedKey = MapVirtualKey( key, 0 );
	event.type = INPUT_KEYBOARD;
	event.ki.dwFlags = KEYEVENTF_SCANCODE;
	event.ki.wScan = mappedKey;
}

void keyMouse::releaseKey(INPUT &event, SHORT key){
	const UINT mappedKey = MapVirtualKey( key, 0 );
	event.type = INPUT_KEYBOARD;
	event.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	event.ki.wScan = mappedKey;
}

void keyMouse::pressMouse(INPUT &event, SHORT key){
	event.type = INPUT_MOUSE;
	if(key == VK_LBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	}else if(key == VK_RBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	}else if (key == VK_MBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
	}else if(key == VK_CUSTOM_SCROLLUP){
		event.mi.dwFlags = MOUSEEVENTF_WHEEL;
		event.mi.mouseData = 120;
	}else if(key == VK_CUSTOM_SCROLLDOWN){
		event.mi.dwFlags = MOUSEEVENTF_WHEEL;
		event.mi.mouseData = -120;
	}
}

void keyMouse::releaseMouse(INPUT &event, SHORT key){
	event.type = INPUT_MOUSE;
	if(key == VK_LBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	}else if(key == VK_RBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	}else if (key == VK_MBUTTON){
		event.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
	}else if(key == VK_CUSTOM_SCROLLUP){
		//Do nothing single press event type
	}else if(key == VK_CUSTOM_SCROLLDOWN){
		//Do nothing single press event type
	}
}

/*
* Builds the list of possible key presses
* Those acceptable in the profile settings must be listed here first
*
* Look here to see the list of possible ones. I haven't added everything yet.
*
* http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
*/
void keyMouse::buildLookupTable(){
	bmap.insert(std::make_pair("KEY_0",VkKeyScan('0')));
	bmap.insert(std::make_pair("KEY_1",VkKeyScan('1')));
	bmap.insert(std::make_pair("KEY_2",VkKeyScan('2')));
	bmap.insert(std::make_pair("KEY_3",VkKeyScan('3')));
	bmap.insert(std::make_pair("KEY_4",VkKeyScan('4')));
	bmap.insert(std::make_pair("KEY_5",VkKeyScan('5')));
	bmap.insert(std::make_pair("KEY_6",VkKeyScan('6')));
	bmap.insert(std::make_pair("KEY_7",VkKeyScan('7')));
	bmap.insert(std::make_pair("KEY_8",VkKeyScan('8')));
	bmap.insert(std::make_pair("KEY_9",VkKeyScan('9')));

	bmap.insert(std::make_pair("KEY_A",VkKeyScan('a')));
	bmap.insert(std::make_pair("KEY_B",VkKeyScan('b')));
	bmap.insert(std::make_pair("KEY_C",VkKeyScan('c')));
	bmap.insert(std::make_pair("KEY_D",VkKeyScan('d')));
	bmap.insert(std::make_pair("KEY_E",VkKeyScan('e')));
	bmap.insert(std::make_pair("KEY_F",VkKeyScan('f')));
	bmap.insert(std::make_pair("KEY_G",VkKeyScan('g')));
	bmap.insert(std::make_pair("KEY_H",VkKeyScan('h')));
	bmap.insert(std::make_pair("KEY_I",VkKeyScan('i')));
	bmap.insert(std::make_pair("KEY_J",VkKeyScan('j')));
	bmap.insert(std::make_pair("KEY_K",VkKeyScan('k')));
	bmap.insert(std::make_pair("KEY_L",VkKeyScan('l')));
	bmap.insert(std::make_pair("KEY_M",VkKeyScan('m')));
	bmap.insert(std::make_pair("KEY_N",VkKeyScan('n')));
	bmap.insert(std::make_pair("KEY_O",VkKeyScan('o')));
	bmap.insert(std::make_pair("KEY_P",VkKeyScan('p')));
	bmap.insert(std::make_pair("KEY_Q",VkKeyScan('q')));
	bmap.insert(std::make_pair("KEY_R",VkKeyScan('r')));
	bmap.insert(std::make_pair("KEY_S",VkKeyScan('s')));
	bmap.insert(std::make_pair("KEY_T",VkKeyScan('t')));
	bmap.insert(std::make_pair("KEY_U",VkKeyScan('u')));
	bmap.insert(std::make_pair("KEY_V",VkKeyScan('v')));
	bmap.insert(std::make_pair("KEY_W",VkKeyScan('w')));
	bmap.insert(std::make_pair("KEY_X",VkKeyScan('x')));
	bmap.insert(std::make_pair("KEY_Y",VkKeyScan('y')));
	bmap.insert(std::make_pair("KEY_Z",VkKeyScan('z')));

	bmap.insert(std::make_pair("KEY_SHIFT",VK_SHIFT));
	bmap.insert(std::make_pair("KEY_BACKSPACE",VK_BACK));
	bmap.insert(std::make_pair("KEY_TAB",VK_TAB));
	bmap.insert(std::make_pair("KEY_ENTER",VK_RETURN));
	bmap.insert(std::make_pair("KEY_CTRL",VK_CONTROL));
	bmap.insert(std::make_pair("KEY_ALT",VK_MENU));
	bmap.insert(std::make_pair("KEY_CAPS",VK_CAPITAL));
	bmap.insert(std::make_pair("KEY_ESC",VK_ESCAPE));
	bmap.insert(std::make_pair("KEY_SPACE",VK_SPACE));

	bmap.insert(std::make_pair("KEY_PAGEUP",VK_PRIOR));
	bmap.insert(std::make_pair("KEY_PAGEDOWN",VK_NEXT));
	bmap.insert(std::make_pair("KEY_HOME",VK_HOME));
	bmap.insert(std::make_pair("KEY_END",VK_END));
	bmap.insert(std::make_pair("KEY_INSERT",VK_INSERT));
	bmap.insert(std::make_pair("KEY_DELETE",VK_DELETE));

	bmap.insert(std::make_pair("KEY_LEFT",VK_LEFT));
	bmap.insert(std::make_pair("KEY_RIGHT",VK_RIGHT));
	bmap.insert(std::make_pair("KEY_DOWN",VK_DOWN));
	bmap.insert(std::make_pair("KEY_UP",VK_UP));

	bmap.insert(std::make_pair("KEY_F1",VK_F1));
	bmap.insert(std::make_pair("KEY_F2",VK_F2));
	bmap.insert(std::make_pair("KEY_F3",VK_F3));
	bmap.insert(std::make_pair("KEY_F4",VK_F4));
	bmap.insert(std::make_pair("KEY_F5",VK_F5));
	bmap.insert(std::make_pair("KEY_F6",VK_F6));
	bmap.insert(std::make_pair("KEY_F7",VK_F7));
	bmap.insert(std::make_pair("KEY_F8",VK_F8));
	bmap.insert(std::make_pair("KEY_F9",VK_F9));
	bmap.insert(std::make_pair("KEY_F10",VK_F10));
	bmap.insert(std::make_pair("KEY_F11",VK_F11));
	bmap.insert(std::make_pair("KEY_F12",VK_F12));

	bmap.insert(std::make_pair("MOUSE_BUTTON_1",VK_LBUTTON));
	bmap.insert(std::make_pair("MOUSE_BUTTON_2",VK_RBUTTON));
	bmap.insert(std::make_pair("MOUSE_BUTTON_3",VK_MBUTTON));

	bmap.insert(std::make_pair("MOUSE_SCROLL_UP",VK_CUSTOM_SCROLLUP));
	bmap.insert(std::make_pair("MOUSE_SCROLL_DOWN",VK_CUSTOM_SCROLLDOWN));
}