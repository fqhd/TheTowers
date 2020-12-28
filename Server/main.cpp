#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <glm/gtc/noise.hpp>
#include <../Client/Constants.hpp>


void generateWorld(uint8_t* data);

int main(){

	//Allocating memory for world data
	uint8_t* data = new uint8_t[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE];

	//Populating the world data buffer
	generateWorld(data);


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
				std::cout << "New client connected: " << sockets.size() << std::endl;

				sf::Packet packet;

				//Compressing the world
				sf::Uint64 numBlocks = 1;
				for(sf::Uint64 i = 0; i < WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE; i++){
					if(data[i - 1] != data[i]){
						packet << (sf::Uint8)data[i - 1] << numBlocks;
						numBlocks = 1;
					}else{
						numBlocks++;
					}
				}
				//Storing the compressed world in the packet
				packet << (sf::Uint8)data[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE - 1] << numBlocks;

				//Sending the packet containing the compressed world to the newly connected person
				socket->send(packet);

			}else{
				for(unsigned int i = 0; i < sockets.size(); i++){
					if(selector.isReady(*sockets[i])){
						sf::Packet packet;
						sf::Status status = sockets[i].receive(packet);
						if(status == sf::Socket::Done){
							for(unsigned int j = 0; j < sockets.size(); j++){
								if(i != j){
									sockets[j]->send(packet);
								}
							}
						}else if(status == sf::Socket::Disconnected){
							std::cout << "This client is disconnected" << std::endl;
						}
					}
				}
			}
		}

	}



     return 0;
}

void generateWorld(uint8_t* data){
	uint8_t* data = new uint8_t[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE];
	for(unsigned int y = 0; y < CHUNK_WIDTH * WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_SIZE; z++){
			for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_SIZE; x++){
				data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = 0;
			}
		}
	}

	for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_SIZE; z++){
		for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_SIZE; x++){

			float p = (glm::perlin(glm::vec2(x * 0.1f / (float)CHUNK_WIDTH * WORLD_SIZE, z * 0.1f / (float)CHUNK_WIDTH * WORLD_SIZE)) + 1.0f) / 2.0f;

			uint32_t height = CHUNK_WIDTH * p;

			for(uint32_t y = 0; y < height; y++){
				data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = y + 100;
			}

		}
	}
}
