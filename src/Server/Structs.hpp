#include <SFML/Network.hpp>
#include <vector>

class Client {
public:
	Client(){
		socket = new sf::TcpSocket();
	}
	sf::TcpSocket* socket = nullptr;
	uint8_t id = 0;
};

struct CompressionSegment {
	uint8_t blockType;
	uint16_t numBlocks;
};

class Chunk {
public:

	void compressData(uint8_t* _data){
		// Compress data and store it into bytes array

	}

	std::vector<CompressionSegment> bytes;
};
