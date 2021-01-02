#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Perlin.hpp"


void getConstantData(unsigned int* worldWidth, unsigned int* worldHeight, unsigned int* chunkWidth);
void generateWorld(uint8_t* data, unsigned int chunkWidth, unsigned int worldWidth, unsigned int worldHeight);

int main(){

	srand(time(0));

	//Varaibles
	unsigned int worldWidth = 0;
	unsigned int worldHeight = 0;
	unsigned int chunkWidth = 0;
	getConstantData(&worldWidth, &worldHeight, &chunkWidth);
	unsigned int chunkSize = chunkWidth * chunkWidth * chunkWidth;


	//Allocating memory for world data
	uint8_t* data = new uint8_t[worldWidth * worldWidth * worldHeight * chunkSize];

	std::cout << "World Size(bytes): " << worldWidth * worldWidth * worldHeight * chunkSize << std::endl;

	//Populating the world data buffer
	generateWorld(data, chunkWidth, worldWidth, worldHeight);


	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;

	std::cout << "Listening for connection..." << std::endl;
	listener.listen(2000);
	selector.add(listener);

	while(true){

		if(selector.wait()){
			if(selector.isReady(listener)){
				sf::TcpSocket* socket = new sf::TcpSocket();
				listener.accept(*socket);
				sockets.push_back(socket);
				selector.add(*socket);
				std::cout << "New client connected with ID: " << sockets.size() << std::endl;

				sf::Packet packet;

				//Compressing the world
				sf::Uint64 numBlocks = 1;
				for(sf::Uint64 i = 1; i < (worldWidth * worldWidth * worldHeight * chunkSize) - 1; i++){
					if(data[i - 1] != data[i]){
						packet << (sf::Uint8)data[i - 1] << numBlocks;
						numBlocks = 1;
					}else{
						numBlocks++;
					}
				}
				packet << (sf::Uint8)data[worldWidth * worldWidth * worldHeight * chunkSize - 1] << numBlocks;

				//Sending the packet containing the compressed world to the newly connected person
				socket->send(packet);

			}else{
				for(unsigned int i = 0; i < sockets.size(); i++){
					if(selector.isReady(*sockets[i])){
						sf::Packet packet;
						sf::Socket::Status status = sockets[i]->receive(packet);

						//Variables for received packet information
						int x;
						int y;
						int z;
						uint8_t b;

						//Depackaging packet
						packet >> x >> y >> z >> b;

						//Updating world data based on sent packet
						if(!(x < 0 || x >= chunkWidth * worldWidth || y < 0 || y >= chunkWidth * worldHeight || z < 0 || z >= chunkWidth * worldWidth)){
							data[(y * chunkWidth * worldWidth * chunkWidth * worldWidth) + (z * chunkWidth * worldWidth) + x] = b;
						}

						//Repackaging packet
						packet << x << y << z << b;

						if(status == sf::Socket::Done){
							for(unsigned int j = 0; j < sockets.size(); j++){
								if(i != j){
									sockets[j]->send(packet);
								}
							}
						}else if(status == sf::Socket::Disconnected){
							std::cout << "Client " << i + 1 << " disconnected" << std::endl;
							sockets[i] = sockets.back();
							sockets.pop_back();
						}
					}
				}
			}
		}

	}



     return 0;
}

void generateWorld(uint8_t* data, unsigned int chunkWidth, unsigned int worldWidth, unsigned int worldHeight){
	//Setting everything to zero to start
	for(unsigned int y = 0; y < chunkWidth * worldHeight; y++){
		for(unsigned int z = 0; z < chunkWidth * worldWidth; z++){
			for(unsigned int x = 0; x < chunkWidth * worldWidth; x++){
				data[(y * chunkWidth * worldWidth * chunkWidth * worldWidth) + (z * chunkWidth * worldWidth) + x] = 0;
			}
		}
	}

	//Generating the world with perlin noise
	Perlin perlin;
	perlin.init(chunkWidth * worldWidth, 6, 0.5f);
	for(unsigned int z = 0; z < chunkWidth * worldWidth; z++){
		for(unsigned int x = 0; x < chunkWidth * worldWidth; x++){

			unsigned int height = perlin.noise(x, z) * chunkWidth * worldHeight;

			for(unsigned int y = 0; y < height; y++){
				data[(y * chunkWidth * worldWidth * chunkWidth * worldWidth) + (z * chunkWidth * worldWidth) + x] = y + 100;
			}

		}
	}
	perlin.destroy();
}

void getConstantData(unsigned int* worldWidth, unsigned int* worldHeight, unsigned int* chunkWidth){

	std::ifstream is;
     std::string s;
     is.open("../constants.donotchange");

     while(is >> s){
          if(s == "ChunkWidth:"){
               is >> *chunkWidth;
          }else if(s == "WorldWidth:"){
               is >> *worldWidth;
          }else if(s == "WorldHeight:"){
               is >> *worldHeight;
          }
     }

     is.close();

}
