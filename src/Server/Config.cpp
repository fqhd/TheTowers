#include "Config.hpp"
#include <iostream>

void Config::loadFromFile(){
    std::ifstream is;
    is.open("Config");
    if(is.fail()){
        std::cout << "Failed to open config" << std::endl;
        return;
    }
    std::string type;
    while(is >> type){
        if(type == "WORLD_WIDTH:"){
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
        }
    }
    is.close();
}

unsigned int Config::getWorldWidth(){
    return m_worldWidth;
}

unsigned int Config::getWorldLength(){
    return m_worldLength;
}

unsigned int Config::getWorldHeight(){
    return m_worldHeight;
}

unsigned int Config::getChunkWidth(){
    return m_chunkWidth;
}

unsigned int Config::getClientPort(){
    return m_clientPort;
}

unsigned int Config::getServerPort(){
    return m_serverPort;
}
