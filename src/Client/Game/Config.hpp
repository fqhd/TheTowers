#pragma once

#include <fstream>

class Config {
public:

	void loadFromFile();

	unsigned int getWorldWidth() const;
	unsigned int getWorldLength() const;
	unsigned int getWorldHeight() const;
	unsigned int getChunkWidth() const;
	unsigned int getClientPort() const;
	unsigned int getServerPort() const;
	unsigned int getPacketTransmissionFrequency() const;
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;
	float getMouseSensitivity() const;


private:

	unsigned int m_worldWidth = 0;
	unsigned int m_worldHeight = 0;
	unsigned int m_worldLength = 0;
	unsigned int m_chunkWidth = 0;
	unsigned int m_clientPort = 0;
	unsigned int m_serverPort = 0;
	unsigned int m_windowWidth = 0;
	unsigned int m_windowHeight = 0;
	unsigned int m_packetTransmissionFrequency = 0;
	float m_mouseSensitivity = 0.0f;

};
