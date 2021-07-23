#include "Settings.hpp"

void Settings::loadFromFile(){
	std::ifstream is;
	is.open("Settings.txt");
	if(is.fail()){
		std::cout << "Settings: Failed to open settings" << std::endl;
		return;
	}
	std::string type;
	while(is >> type){
		if(type == "isFogToggled:"){
			is >> isFogToggled;
		}else if(type == "isVignetteToggled:"){
			is >> isVignetteToggled;
		}else if(type == "isDebugToggled:"){
			is >> isDebugToggled;
		}else if(type == "renderOutline:"){
			is >> renderOutline;
		}
	}
	is.close();
}

void Settings::writeToFile(){
	std::ofstream os;
	os.open("Settings.txt");
	if(os.fail()){
		std::cout << "Failed to open settings" << std::endl;
		return;
	}
	os << "isFogToggled: " << isFogToggled << std::endl;
	os << "isVignetteToggled: " << isVignetteToggled << std::endl;
	os << "isDebugToggled: " << isDebugToggled << std::endl;
	os << "renderOutline: " << renderOutline << std::endl;
	os.close();
}
