#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include "../Client/Constants.hpp"

int main(){

	uint8_t* data = new uint8_t[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE];

	for(unsigned int y = 0; y < CHUNK_WIDTH * WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_SIZE; z++){
			for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_SIZE; x++){
				data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = 0;
				if(y <= 5){
					data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = 215;
				}
			}
		}
	}

	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;

	std::cout << "Listening for connection" << std::endl;
	listener.listen(2000);
	selector.add(listener);


	while(true){

		if(selector.wait()){
			if(selector.isReady(listener)){
				sf::TcpSocket* socket = new sf::TcpSocket();
				listener.accept(*socket);
				sockets.push_back(socket);
				selector.add(*socket);
				std::cout << "Connected on with ID: " << sockets.size() << std::endl;


				sf::Packet packet;

				sf::Uint64 numBlocks = 1;
				for(sf::Uint64 i = 0; i < WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE; i++){
					if(data[i - 1] != data[i]){
						packet << (sf::Uint8)data[i - 1] << numBlocks;
						numBlocks = 1;
					}else{
						numBlocks++;
					}
				}
				packet << (sf::Uint8)data[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE - 1] << numBlocks;

				socket->send(packet);

			}else{
				for(unsigned int i = 0; i < sockets.size(); i++){
					if(selector.isReady(*sockets[i])){
						sf::Packet packet;
						if(sockets[i]->receive(packet) == sf::Socket::Done){

							// sf::Uint8 blockX = 0;
							// sf::Uint8 blockY = 0;
							// sf::Uint8 blockZ = 0;
							// sf::Uint8 blockID = 0;
							// float playerX = 0.0f;
							// float playerY = 0.0f;
							// float playerZ = 0.0f;
							//
							// packet >> blockX >> blockY >> blockZ >> blockID >> playerX >> playerY >> playerZ;
							//
							// data[(blockY * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (blockZ * CHUNK_WIDTH * WORLD_SIZE) + blockX] = blockID;
							//
							// packet << blockX << blockY << blockZ << blockID << playerX << playerY << playerZ << (sf::Uint8)(i + 1);
							packet << (sf::Uint8)(i + 1);


							for(unsigned int j = 0; j < sockets.size(); j++){
								if(i != j){
									sockets[j]->send(packet);
								}
							}
						}
					}
				}
			}
		}

	}



     return 0;
}
