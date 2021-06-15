#include <SFML/Network.hpp>

class Client {
public:
	Client(){
		socket = new sf::TcpSocket();
	}
	sf::TcpSocket* socket = nullptr;
	uint8_t id = 0;
};
