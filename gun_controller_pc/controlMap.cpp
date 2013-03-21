#include "controlMap.h"

microController::dataStorage data;
microController micro;

std::string digArr[64];
bool digInv[64];
std::vector<controlMap::virtualButton> virtualBtn;

typedef std::map<std::string, motionProcess::analogValues> analogMap;
typedef std::map<std::string, std::string> keyMap;

keyMap kmap;
analogMap amap;

CIniReader iniReadSet(".\\settings.ini");
CIniWriter iniWriteSet(".\\settings.ini");

CIniReader iniReadProf(".\\profiles.ini");
CIniWriter iniWriteProf(".\\profiles.ini");

controlMap::controlMap(){
	microController microNew(iniReadSet.ReadInteger("General","comPort",16)-1);
	micro = microNew;
	controlMap::readSettings();
	controlMap::readAnalogSetting();
}

void controlMap::getMapping(){}


void controlMap::getData(std::vector<std::string> * buttons, motionProcess::motionData * moData){
	micro.updateData(&data);//blocks until the uC sends a full frame of data
	translateButtons(buttons);
	translateVirtualButtons(buttons);
	copyMotionData(moData);
}


void controlMap::copyMotionData(motionProcess::motionData * moData){
	analogMap::iterator itr;

	for(itr = amap.begin(); itr != amap.end(); ++itr){
		//Copy the current value into the structure
		if(itr->second.index == 0){
			itr->second.value = data.analog_1;
		}else if(itr->second.index == 1){
			itr->second.value = data.analog_2;
		}else if(itr->second.index == 2){
			itr->second.value = data.analog_3;
		}else if(itr->second.index == 3){
			itr->second.value = data.analog_4;
		}else if(itr->second.index == 4){
			itr->second.value = data.analog_5;
		}else if(itr->second.index == 5){
			itr->second.value = data.analog_6;
		}else if(itr->second.index == 6){
			itr->second.value = data.analog_7;
		}else if(itr->second.index == 7){
			itr->second.value = data.analog_8;
		}else if(itr->second.index == 8){
			itr->second.value = data.analog_9;
		}else if(itr->second.index == 9){
			itr->second.value = data.analog_10;
		}else if(itr->second.index == 10){
			itr->second.value = data.analog_11;
		}else if(itr->second.index == 11){
			itr->second.value = data.analog_12;
		}else if(itr->second.index == 12){
			itr->second.value = data.analog_13;
		}else if(itr->second.index == 13){
			itr->second.value = data.analog_14;
		}else if(itr->second.index == 14){
			itr->second.value = data.analog_15;
		}else if(itr->second.index == 15){
			itr->second.value = data.analog_16;
		}


		if(itr->first == "gyro_x"){
			moData->gyro_x = itr->second;
		}else if(itr->first == "gyro_y"){
			moData->gyro_y = itr->second;
		}else if(itr->first == "gyro_z"){
			moData->gyro_z = itr->second;
		}else if(itr->first == "gyro_4_x"){
			moData->gyro_4_x = itr->second;
		}else if(itr->first == "gyro_4_y"){
			moData->gyro_4_y = itr->second;
		}else if(itr->first == "gyro_4_z"){
			moData->gyro_4_z = itr->second;
		}else if(itr->first == "accel_x"){
			moData->accel_x = itr->second;
		}else if(itr->first == "accel_y"){
			moData->accel_y = itr->second;
		}else if(itr->first == "accel_z"){
			moData->accel_z = itr->second;
		}else if(itr->first == "mag_x"){
			moData->mag_x = itr->second;
		}else if(itr->first == "mag_y"){
			moData->mag_y = itr->second;
		}else if(itr->first == "mag_z"){
			moData->mag_z = itr->second;
		}
	}
}


void controlMap::translateVirtualButtons(std::vector<std::string> * buttons){
	for(int i=0;i<virtualBtn.size();i++){
		uint16_t value;
		if(amap[virtualBtn[i].input].index == 0){
			//analog_1
			value = data.analog_1;
		}else if(amap[virtualBtn[i].input].index == 1){
			//analog_2
			value = data.analog_2;
		}else if(amap[virtualBtn[i].input].index == 2){
			//analog_3
			value = data.analog_3;
		}else if(amap[virtualBtn[i].input].index == 3){
			//analog_4
			value = data.analog_4;
		}else if(amap[virtualBtn[i].input].index == 4){
			//analog_5
			value = data.analog_5;
		}else if(amap[virtualBtn[i].input].index == 5){
			//analog_6
			value = data.analog_6;
		}else if(amap[virtualBtn[i].input].index == 6){
			//analog_7
			value = data.analog_7;
		}else if(amap[virtualBtn[i].input].index == 7){
			//analog_8
			value = data.analog_8;
		}else if(amap[virtualBtn[i].input].index == 8){
			//analog_9
			value = data.analog_9;
		}else if(amap[virtualBtn[i].input].index == 9){
			//analog_10
			value = data.analog_10;
		}else if(amap[virtualBtn[i].input].index == 10){
			//analog_11
			value = data.analog_11;
		}else if(amap[virtualBtn[i].input].index == 11){
			//analog_12
			value = data.analog_12;
		}else if(amap[virtualBtn[i].input].index == 12){
			//analog_13
			value = data.analog_13;
		}else if(amap[virtualBtn[i].input].index == 13){
			//analog_14
			value = data.analog_14;
		}else if(amap[virtualBtn[i].input].index == 14){
			//analog_15
			value = data.analog_15;
		}else if(amap[virtualBtn[i].input].index == 15){
			//analog_16
			value = data.analog_16;
		}
		if(virtualBtn[i].trigger == "HIGH"){
			if(value > amap[virtualBtn[i].input].mid + virtualBtn[i].deadzone){
				buttons->push_back(kmap[virtualBtn[i].output]);
			}
		}else if(virtualBtn[i].trigger == "LOW"){
			if(value< amap[virtualBtn[i].input].mid - virtualBtn[i].deadzone){
				buttons->push_back(kmap[virtualBtn[i].output]);
			}
		}
	}
}


void controlMap::translateButtons(std::vector<std::string> * buttons){
	uint16_t mask = 0x8000;
	for(int i=0;i<64;i++){
		if(i < 16){
			if(digInv[i] == false){
				if(!(data.digital_1 & mask)){
					buttons->push_back(kmap[digArr[i]]);
				}
			}else{
				if(data.digital_1 & mask){
					buttons->push_back(kmap[digArr[i]]);
				}
			}
		}else if(i < 32){
			if(digInv[i] == false){
				if(!(data.digital_2 & mask)){
					buttons->push_back(kmap[digArr[i]]);
				}
			}else{
				if(data.digital_2 & mask){
					buttons->push_back(kmap[digArr[i]]);
				}
			}
		}else if(i < 48){
			if(digInv[i] == false){
				if(!(data.digital_3 & mask)){
					buttons->push_back(kmap[digArr[i]]);
				}
			}else{
				if(data.digital_3 & mask){
					buttons->push_back(kmap[digArr[i]]);
				}
			}
		}else if(i < 64){
			if(digInv[i] == false){
				if(!(data.digital_4 & mask)){
					buttons->push_back(kmap[digArr[i]]);
				}
			}else{
				if(data.digital_4 & mask){
					buttons->push_back(kmap[digArr[i]]);
				}
			}
		}
		mask = mask >> 1;
		//Ensure that mask rolls over for the next 16 bits
		if(mask == 0x00){
			mask = 0x8000;
		}
	}
}


void controlMap::readAnalogSetting(){
	char buffer[255];
	char  * read;

	//Read the analog control mapping
	for(int i=0;i<16;i++){
		motionProcess::analogValues analog;
		sprintf(buffer,"analog_%d",(i+1));
		read = iniReadSet.ReadString("ControlMap",buffer,"undefined");
		std::string temp(read);
		analog.name = temp;
		sprintf(buffer,"analog_min_%d",(i+1));
		int min = iniReadSet.ReadInteger("ControlMap",buffer,0);
		analog.min = min;
		sprintf(buffer,"analog_max_%d",(i+1));
		int max = iniReadSet.ReadInteger("ControlMap",buffer,0);
		analog.max = max;
		sprintf(buffer,"analog_mid_%d",(i+1));
		int mid = iniReadSet.ReadInteger("ControlMap",buffer,0);
		analog.mid = mid;
		sprintf(buffer,"analog_deadzone_%d",(i+1));
		int deadzone = iniReadSet.ReadInteger("ControlMap",buffer,0);
		analog.deadzone = deadzone;
		analog.index = i;
		amap.insert(std::make_pair(temp,analog));
	}
}


//
//Read from the settings ini file
//
void controlMap::readSettings(){
	char buffer[255];
	char  * read;
	bool invert;

	//Read the control mapping
	for(int i=0;i<64;i++){
		sprintf(buffer,"digital_%d",(i+1));
		read = iniReadSet.ReadString("ControlMap",buffer,"undefined");
		std::string temp(read);
		digArr[i] = temp;
	}

	//Read if any of the controls are inverted
	for(int i=0;i<64;i++){
		sprintf(buffer,"digital_invert_%d",(i+1));
		invert = iniReadSet.ReadBoolean("ControlMap",buffer,false);
		digInv[i] = invert;
	}

	//Read in the virtual buttons
	int numVirtual = iniReadSet.ReadInteger("ControlMap","virtual_count",0);
	
	for(int i=0;i<numVirtual;i++){
		virtualButton btns;
		sprintf(buffer,"virtual_input_%d",(i+1));
		btns.input = iniReadSet.ReadString("ControlMap",buffer,"undefined");
		sprintf(buffer,"virtual_output_%d",(i+1));
		btns.output = iniReadSet.ReadString("ControlMap",buffer,"undefined");
		sprintf(buffer,"virtual_deadzone_%d",(i+1));
		btns.deadzone = iniReadSet.ReadInteger("ControlMap",buffer,0);
		sprintf(buffer,"virtual_trigger_%d",(i+1));
		btns.trigger = iniReadSet.ReadString("ControlMap",buffer,"undefined");
		virtualBtn.push_back(btns);
	}

	//Read the current profile in
	int curProf = iniReadProf.ReadInteger("General","currentProfile",1);

	for(int i=0;i<64;i++){
		if(strcmp(digArr[i].c_str(),"undefined")!=0){
			char *option = const_cast<char*> ( digArr[i].c_str() );
			sprintf(buffer,"Profile_%d",curProf);
			read = iniReadProf.ReadString(buffer,option,"undefined");
			//Add it to the key map
			std::string temp(read);
			kmap.insert(std::make_pair(digArr[i], temp));
		}
	}

	//Now add the virtual buttons for the profile
	for(int i=0;i<virtualBtn.size();i++){
		if(strcmp(virtualBtn[i].input.c_str(),"undefined")!=0 && strcmp(virtualBtn[i].output.c_str(),"undefined")!=0 ){
			char *option = const_cast<char*> ( virtualBtn[i].output.c_str() );
			read = iniReadProf.ReadString("Profile_1",option,"undefined");
			//Add it to the key map
			std::string temp(read);
			kmap.insert(std::make_pair(virtualBtn[i].output, temp));
		}
	}
}


void controlMap::initSettings(){
	char buffer[255];
	
	for(int i=1;i<17;i++){
		sprintf(buffer,"analog_%d",i);
		iniWriteSet.WriteString("ControlMap",buffer,"undefined");
	}

	for(int i=1;i<65;i++){
		sprintf(buffer,"digital_%d",i);
		iniWriteSet.WriteString("ControlMap",buffer,"undefined");
	}

	for(int i=1;i<65;i++){
		sprintf(buffer,"digital_invert_%d",i);
		iniWriteSet.WriteBoolean("ControlMap",buffer,false);
	}
}
