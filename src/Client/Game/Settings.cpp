#include "Settings.hpp"
#include "FilePathManager.hpp"

void Settings::loadFromFile(){
	std::ifstream is;
	is.open(FilePathManager::getRootFolderDirectory() + "Settings.txt");
	if(is.fail()){
		std::cout << "Settings: Failed to open Settings.txt" << std::endl;
		return;
	}
	std::string type;
	while(is >> type){
		if(type == "isVignetteToggled:"){
			is >> isVignetteToggled;
		}else if(type == "isDebugToggled:"){
			is >> isDebugToggled;
		}else if(type == "legacyOutline:"){
			is >> legacyOutline;
		}
	}
	is.close();
}

void Settings::writeToFile(){
	std::ofstream os;
	os.open("Settings.txt");
	if(os.fail()){
		std::cout << "Failed to open Settings.txt" << std::endl;
		return;
	}
	os << "isVignetteToggled: " << isVignetteToggled << std::endl;
	os << "isDebugToggled: " << isDebugToggled << std::endl;
	os << "legacyOutline: " << legacyOutline << std::endl;
	os.close();
}
