#include "Constants.hpp"
#include "Utils.hpp"
#include <fstream>


unsigned int Constants::m_screenWidth;
unsigned int Constants::m_screenHeight;
unsigned int Constants::m_chunkWidth;
unsigned int Constants::m_worldWidth;
unsigned int Constants::m_worldHeight;
unsigned int Constants::m_localWorldWidth;
unsigned int Constants::m_localWorldHeight;
unsigned int Constants::m_numParticles;
float Constants::m_playerReachDistance;
float Constants::m_occlusionFactor;
unsigned int Constants::m_precision;
float Constants::m_maxPlayerSpeed;
float Constants::m_gravity;
float Constants::m_entityMovementSharpness;
unsigned int Constants::m_maxRenderDistance;
float Constants::m_maxMouseSensibility;
float Constants::m_maxDensity;
float Constants::m_maxGradient;
unsigned short Constants::m_clientPort;
unsigned short Constants::m_serverPort;
unsigned short Constants::m_serverListeningPort;
unsigned int Constants::m_packetTransmissionFrequency;

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
          }else if(s == "LocalWorldWidth:"){
               is >> m_localWorldWidth;
          }else if(s == "LocalWorldHeight:"){
               is >> m_localWorldHeight;
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
          }else if(s == "LocalWorldWidth:"){
               is >> m_localWorldWidth;
          }else if(s == "LocalWorldHeight:"){
               is >> m_localWorldHeight;
          }else if(s == "NumParticles:"){
               is >> m_numParticles;
          }else if(s == "MaxGradient:"){
               is >> m_maxGradient;
          }else if(s == "MaxDensity:"){
               is >> m_maxDensity;
		}else if(s == "ClientPort:"){
			is >> m_clientPort;
		}else if(s == "ServerPort:"){
			is >> m_serverPort;
		}else if(s == "ServerListeningPort:"){
			is >> m_serverListeningPort;
		}else if(s == "PacketTransmissionFrequency:"){
			is >> m_packetTransmissionFrequency;
		}else if(s == "EntityMovementSharpness:"){
               is >> m_entityMovementSharpness;
          }
     }

     is.close();

}

unsigned int Constants::getNumParticles(){
     return m_numParticles;
}

unsigned int Constants::getLocalWorldWidth(){
     return m_localWorldWidth;
}

unsigned short Constants::getClientPort(){
	return m_clientPort;
}

unsigned short Constants::getServerPort(){
	return m_serverPort;
}

unsigned short Constants::getServerListeningPort(){
	return m_serverListeningPort;
}

float Constants::getMaxGradient(){
     return m_maxGradient;
}

float Constants::getMaxDensity(){
     return m_maxDensity;
}

float Constants::getEntityMovementSharpness(){
     return m_entityMovementSharpness;
}

unsigned int Constants::getLocalWorldHeight(){
     return m_localWorldHeight;
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

unsigned int Constants::getPacketTransmissionFrequency(){
	return m_packetTransmissionFrequency;
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

void Constants::printDebugMessage() {
     Utils::printDividor("Constants");
     Utils::log("ScreenWidth: " + std::to_string(m_screenWidth));
     Utils::log("ScreenHeight: " + std::to_string(m_screenHeight));
     Utils::log("ChunkWidth: " + std::to_string(m_chunkWidth));
     Utils::log("ChunkSize: " + std::to_string(m_chunkWidth * m_chunkWidth * m_chunkWidth));
     Utils::log("LocalWorldWidth: " + std::to_string(m_localWorldWidth));
     Utils::log("LocalWorldHeight: " + std::to_string(m_localWorldHeight));
     Utils::log("WorldWidth: " + std::to_string(m_worldWidth));
     Utils::log("WorldHeight: " + std::to_string(m_worldHeight));
     Utils::log("PlayerReachDistance: " + std::to_string(m_playerReachDistance));
     Utils::log("OcclusionFactor: " + std::to_string(m_occlusionFactor));
     Utils::log("Precision: " + std::to_string(m_precision));
     Utils::log("MaxPlayerSpeed: " + std::to_string(m_maxPlayerSpeed));
     Utils::log("Gravity: " + std::to_string(m_gravity));
     Utils::log("MaxRenderDistance: " + std::to_string(m_maxRenderDistance));
     Utils::log("MaxMouseSensibility: " + std::to_string(m_maxMouseSensibility));
	Utils::log("ClientPort: " + std::to_string(m_clientPort));
	Utils::log("ServerPort: " + std::to_string(m_serverPort));
	Utils::log("ServerListeningPort: " + std::to_string(m_serverListeningPort));
	Utils::log("PacketTransmissionFrequency: " + std::to_string(m_packetTransmissionFrequency));
}
