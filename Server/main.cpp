#include <SFML/Network.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <map>
#include "Perlin.hpp"
#include "UtilityFunctions.hpp"


void udpThread(){

	//Variables for algorithm
	Constants constants = getConstants();
	sf::UdpSocket socket;
	socket.bind(constants.udpPort);
	socket.setBlocking(false);

	sf::Packet receivedPacket;
	sf::IpAddress remoteIp;
	unsigned short remotePort;
	while(true){

		if(socket.receive(receivedPacket, remoteIp, remotePort) == sf::Socket::Done){
			std::cout << "received data" << std::endl;
		}

		//Depackaging and printing packet
		glm::vec3 position;
		glm::vec3 forward;
		receivedPacket >> position.x >> position.y >> position.z;
		receivedPacket >> forward.x >> forward.y >> forward.z;

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}


}

int main(){

	srand(time(0));

	//Getting constants
	Constants constants = getConstants();

	//Printing the constants for debug
	std::cout << "ChunkWidth: " << constants.chunkWidth << std::endl;
	std::cout << "WorldWidth: " << constants.worldWidth << std::endl;
	std::cout << "WorldHeight: " << constants.worldHeight << std::endl;
	std::cout << "TcpPort: " << constants.tcpPort << std::endl;
	std::cout << "UdpPort: " << constants.udpPort << std::endl;


	unsigned int ww = constants.worldWidth; //WorldWidth
	unsigned int wh = constants.worldHeight; //WorldHeight
	unsigned int cw = constants.chunkWidth; //ChunkWidth
	unsigned int cs = cw * cw * cw; //ChunkSize

	//Allocating memory for world data
	uint8_t* data = new uint8_t[ww * ww * wh * cs];

	std::cout << "World Size(bytes): " << ww * ww * wh * cs << std::endl;

	//Populating the world data buffer
	generateWorld(data, constants);

	//Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;

	//Starting packet position thread
	std::thread positionUpdater(udpThread);

	//Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(constants.tcpPort);
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
				for(sf::Uint64 i = 1; i < (ww * ww * wh * cs) - 1; i++){
					if(data[i - 1] != data[i]){
						packet << (sf::Uint8)data[i - 1] << numBlocks;
						numBlocks = 1;
					}else{
						numBlocks++;
					}
				}
				packet << (sf::Uint8)data[ww * ww * wh * cs - 1] << numBlocks;

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
						if(!(x < 0 || x >= cw * ww || y < 0 || y >= cw * wh || z < 0 || z >= cw * ww)){
							data[(y * cw * ww * cw * ww) + (z * cw * ww) + x] = b;
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

void generateWorld(uint8_t* data, const Constants& constants){
	//Setting everything to zero to start
	unsigned int cw = constants.chunkWidth; //ChunkWidth
	unsigned int ww = constants.worldWidth; //WorldWidth
	unsigned int wh = constants.worldHeight; //WorldHeight
	for(unsigned int y = 0; y < cw * wh; y++){
		for(unsigned int z = 0; z < cw * ww; z++){
			for(unsigned int x = 0; x < cw * ww; x++){
				data[(y * cw * ww * cw * ww) + (z * cw * ww) + x] = 0;
			}
		}
	}

	//Generating the world with perlin noise
	Perlin perlin;
	perlin.init(cw * ww, 6, 0.5f);
	for(unsigned int z = 0; z < cw * ww; z++){
		for(unsigned int x = 0; x < cw * ww; x++){

			unsigned int height = perlin.noise(x, z) * cw * wh;

			for(unsigned int y = 0; y < height; y++){
				data[(y * cw * ww * cw * ww) + (z * cw * ww) + x] = y + 100;
			}

		}
	}
	perlin.destroy();
}

Constants getConstants(){

	Constants constants;

	std::ifstream is;
     std::string s;
     is.open("../constants.donotchange");

     while(is >> s){
          if(s == "ChunkWidth:"){
               is >> constants.chunkWidth;
          }else if(s == "WorldWidth:"){
               is >> constants.worldWidth;
          }else if(s == "WorldHeight:"){
               is >> constants.worldHeight;
          }else if(s == "TcpPort:"){
			is >> constants.tcpPort;
		}else if(s == "UdpPort:"){
			is >> constants.udpPort;
		}
     }




     is.close();

	return constants;

}
