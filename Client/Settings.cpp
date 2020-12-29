#include "Settings.hpp"
#include <fstream>
#include <string>
#include "Utils.hpp"


void Settings::readFromFile(){

     std::ifstream is;
     std::string s;
     is.open("res/settings.txt");
     if(is.fail()){
          Utils::log("Settings: Unable to locate settings.txt in res/ directory");
          is.close();
          return;
     }
     while(is >> s){
          if(s == "Vsync:"){
               is >> vsync;
          }else if(s == "ShowFPS:"){
               is >> showFPS;
          }else if(s == "Front:"){
               is >> front;
          }else if(s == "Back:"){
               is >> back;
          }else if(s == "Up:"){
               is >> up;
          }else if(s == "Down:"){
               is >> down;
          }else if(s == "Left:"){
               is >> left;
          }else if(s == "Right:"){
               is >> right;
          }
     }
     is.close();

}

void Settings::writeToFile(){
     std::ofstream os;
     os.open("res/settings.txt");
     if(os.fail()){
          Utils::log("Settings: Failed to locate settings.txt in res/ directory");
          os.close();
          return;
     }
     os << "ShowFPS: " << showFPS << std::endl;
     os << "Vsync: " << vsync << std::endl;
     os << "Front: " << front << std::endl;
     os << "Back: " << back << std::endl;
     os << "Up: " << up << std::endl;
     os << "Down: " << down << std::endl;
     os << "Left: " << left << std::endl;
     os << "Right: " << right << std::endl;
     os.close();

}
