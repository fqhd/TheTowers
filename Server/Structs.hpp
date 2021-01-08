#include <SFML/Network.hpp>

struct Constants {
	unsigned int worldWidth = 0;
	unsigned int worldHeight = 0;
	unsigned int chunkWidth = 0;
	unsigned short clientPort = 0;
	unsigned short serverPort = 0;
	unsigned short serverListeningPort = 0;
};

class Client {
public:
	Client(){
		socket = new sf::TcpSocket();
	}
	sf::TcpSocket* socket = nullptr;
	uint8_t id = 0;
};
