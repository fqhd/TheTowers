struct Constants {
	unsigned int worldWidth = 0;
	unsigned int worldHeight = 0;
	unsigned int chunkWidth = 0;
	unsigned short tcpPort = 0;
	unsigned short udpPort = 0;
};

Constants getConstants();
void generateWorld(uint8_t* data, const Constants& constants);
