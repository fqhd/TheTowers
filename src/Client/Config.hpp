#pragma once

#include <fstream>

class Config {
public:

    void loadFromFile();

    float getCameraSpeed();
    unsigned int getWorldWidth();
    unsigned int getWorldLength();
    unsigned int getWorldHeight();
    unsigned int getChunkWidth();
    unsigned int getClientPort();
    unsigned int getServerPort();
    unsigned int getPacketTransmissionFrequency();

private:

    float m_cameraSpeed = 0.0f;
    unsigned int m_worldWidth = 0;
    unsigned int m_worldHeight = 0;
    unsigned int m_worldLength = 0;
    unsigned int m_chunkWidth = 0;
    unsigned int m_clientPort = 0;
    unsigned int m_serverPort = 0;
    unsigned int m_packetTransmissionFrequency = 0;
};
