#include "Config.hpp"
#include <iostream>

void Config::loadFromFile() {
	std::ifstream is;
	is.open("Config");
	if(is.fail()){
		std::cout << "Failed to open config" << std::endl;
			return;
	}
	std::string type;
	while(is >> type){
		if(type == "MOUSE_SENSITIVITY:"){
			is >> m_mouseSensitivity;
		}else if(type == "WORLD_WIDTH:"){
			is >> m_worldWidth;
		}else if(type == "WORLD_HEIGHT:"){
			is >> m_worldHeight;
		}else if(type == "WORLD_LENGTH:"){
			is >> m_worldLength;
		}else if(type == "CHUNK_WIDTH:"){
			is >> m_chunkWidth;
		}else if(type == "CLIENT_PORT:"){
			is >> m_clientPort;
		}else if(type == "SERVER_PORT:"){
			is >> m_serverPort;
		}else if(type == "PACKET_TRANSMISSION_FRQUENCY:"){
			is >> m_packetTransmissionFrequency;
		}else if (type == "WINDOW_WIDTH:"){
			is >> m_windowWidth;
		}else if (type == "WINDOW_HEIGHT:"){
			is >> m_windowHeight;
		}
	}
	is.close();
}

unsigned int Config::getWindowWidth() const {
	return m_windowWidth;
}

unsigned int Config::getWindowHeight() const {
	return m_windowHeight;
}

unsigned int Config::getPacketTransmissionFrequency() const {
	return m_packetTransmissionFrequency;
}

unsigned int Config::getWorldWidth() const {
	return m_worldWidth;
}

unsigned int Config::getWorldLength() const {
	return m_worldLength;
}

unsigned int Config::getWorldHeight() const {
	return m_worldHeight;
}

unsigned int Config::getChunkWidth() const {
	return m_chunkWidth;
}

unsigned int Config::getClientPort() const {
	return m_clientPort;
}

unsigned int Config::getServerPort() const {
	return m_serverPort;
}

float Config::getMouseSensitivity() const {
	return m_mouseSensitivity;
}
