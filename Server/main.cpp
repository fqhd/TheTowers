#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main(){

     sf::TcpListener listener;
     sf::TcpSocket socket;

     uint8_t* data = new uint8_t[128*128*32];

     for(unsigned int y = 0; y < 32; y++){
		for(unsigned int z = 0; z < 32 * 4; z++){
			for(unsigned int x = 0; x < 32 * 4; x++){

				data[(y * 32 * 4 * 32 * 4) + (z * 32 * 4) + x] = (y == 5 ? 50 : 0);

			}
		}
	}

     std::cout << "Listening for connection" << std::endl;
     listener.listen(2000);
     listener.accept(socket);
     std::cout << "Connected to Client" << std::endl;

     socket.send("Hello", 6);

     return 0;
}
