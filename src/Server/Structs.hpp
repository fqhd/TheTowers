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
	CompressionSegment(uint8_t _blockType, uint16_t _numBlocks){
		blockType = _blockType;
		numBlocks = _numBlocks;
	}
	uint8_t blockType;
	uint16_t numBlocks;
};

class Chunk {
public:

	Chunk(){
		bytes.push_back(CompressionSegment(1, 32));
	}

	void compressData(uint8_t* _data){
		// Compress data and store it into bytes array

	}

	std::vector<CompressionSegment> bytes;
};
