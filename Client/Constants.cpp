#include "Constants.hpp"
#include <fstream>

unsigned int Constants::m_screenWidth;
unsigned int Constants::m_screenHeight;
unsigned int Constants::m_chunkWidth;
unsigned int Constants::m_chunkSize;
unsigned int Constants::m_worldWidth;
unsigned int Constants::m_worldHeight;
float Constants::m_playerReachDistance;
float Constants::m_occlusionFactor;
unsigned int Constants::m_precision;
float Constants::m_maxPlayerSpeed;
float Constants::m_gravity;
unsigned int Constants::m_maxRenderDistance;
float Constants::m_maxMouseSensibility;

void Constants::loadFromFile(){

     std::ifstream is;
     std::string s;
     is.open("../constants.donotchange");

     while(is >> s){
          if(s == "ScreenWidth:"){
               is >> m_screenWidth;
          }else if(s == "ScreenHeight:"){
               is >> m_screenHeight;
          }else if(s == "ChunkWidth:"){
               is >> m_chunkWidth;
          }else if(s == "WorldWidth:"){
               is >> m_worldWidth;
          }else if(s == "WorldHeight:"){
               is >> m_worldHeight;
          }else if(s == "PlayerReachDistance:"){
               is >> m_playerReachDistance;
          }else if(s == "OcclusionFactor:"){
               is >> m_occlusionFactor;
          }else if(s == "Precision:"){
               is >> m_precision;
          }else if(s == "MaxPlayerSpeed:"){
               is >> m_maxPlayerSpeed;
          }else if(s == "Gravity:"){
               is >> m_gravity;
          }else if(s == "MaxRenderDistance:"){
               is >> m_maxRenderDistance;
          }else if(s == "MaxMouseSensibility:"){
               is >> m_maxMouseSensibility;
          }
     }

     is.close();

}

unsigned int Constants::getScreenWidth() {
     return m_screenWidth;
}

unsigned int Constants::getScreenHeight() {
     return m_screenHeight;
}

float Constants::getGravity() {
     return m_gravity;
}

float Constants::getMaxPlayerSpeed(){
     return m_maxPlayerSpeed;
}

unsigned int Constants::getChunkWidth() {
     return m_chunkWidth;
}

float Constants::getMaxMouseSensibility(){
     return m_maxMouseSensibility;
}

unsigned int Constants::getMaxRenderDistance(){
     return m_maxRenderDistance;
}

unsigned int Constants::getChunkSize() {
     return m_chunkWidth * m_chunkWidth * m_chunkWidth;
}

unsigned int Constants::getWorldWidth() {
     return m_worldWidth;
}

unsigned int Constants::getWorldHeight() {
     return m_worldHeight;
}

float Constants::getPlayerReachDistance() {
     return m_playerReachDistance;
}

float Constants::getOcclusionFactor() {
     return m_occlusionFactor;
}

unsigned int Constants::getPrecision(){
     return m_precision;
}
