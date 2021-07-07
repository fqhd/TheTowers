#include "Settings.hpp"

void Settings::loadFromFile(){
    std::ifstream is;
    is.open("Settings.txt");
    if(is.fail()){
        std::cout << "Failed to open settings" << std::endl;
        return;
    }
    std::string type;
    while(is >> type){
        if(type == "isFogToggled:"){
            is >> isFogToggled;
        }
    }
}

void Settings::writeToFile(){
    std::ofstream os;
    os.open("Settings.txt");
    if(os.fail()){
        std::cout << "Failed to open settings" << std::endl;
        return;
    }
    os << "isFogToggled: " << isFogToggled;
    os.close();
}
