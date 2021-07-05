#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>

class Config {
public:

    void loadFromFile();

    unsigned int getWorldWidth();
    unsigned int getWorldLength();
    unsigned int getWorldHeight();
    unsigned int getChunkWidth();
    unsigned int getClientPort();
    unsigned int getServerPort();

private:

    unsigned int m_worldWidth = 0;
    unsigned int m_worldHeight = 0;
    unsigned int m_worldLength = 0;
    unsigned int m_chunkWidth = 0;
    unsigned int m_clientPort = 0;
    unsigned int m_serverPort = 0;
};

#endif
