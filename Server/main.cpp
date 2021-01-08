#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <unordered_map>
#include "Structs.hpp"
#include "Perlin.hpp"


//Forward Declarations
Constants getConstants();
void generateWorld(uint8_t* data, const Constants& constants);
void printConstants(const Constants& constants);
uint8_t createUniqueID();
bool doesIDExist(uint8_t id);


//Global Variables
std::vector<Client> clients;

void udpThread(){

	// Getting constants
	Constants constants = getConstants();

	printConstants(constants);

	//Variables for algorithm
	sf::UdpSocket socket;
	sf::Packet receivedPacket;
	sf::IpAddress remoteIp;
	unsigned short remotePort;

	//Initializing variables
	socket.bind(constants.serverPort);
	socket.setBlocking(false);

	while(true){
		receivedPacket.clear();

		while(socket.receive(receivedPacket, remoteIp, remotePort) == sf::Socket::Done){
			std::cout << "got data" << std::endl;

			// uint8_t id = 0;
			// receivedPacket >> id;
			// receivedPacket << id;
			// std::cout << id << std::endl;

			// While we receive packets from clients, we send them to other clients
			// for(auto it = clients.begin(); it != clients.end(); it++){
			// 	socket.send(receivedPacket, it->second.ip, it->second.port);
			// }

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}


}

int main(){

	srand(time(0));

	//Getting constants
	Constants constants = getConstants();

	unsigned int ww = constants.worldWidth; // WorldWidth
	unsigned int wh = constants.worldHeight; // WorldHeight
	unsigned int cw = constants.chunkWidth; // ChunkWidth
	unsigned int cs = cw * cw * cw; // ChunkSize

	//Allocating memory for world data
	uint8_t* data = new uint8_t[ww * ww * wh * cs];

	std::cout << "World Size(bytes): " << ww * ww * wh * cs << std::endl;

	//Populating the world data buffer
	generateWorld(data, constants);

	//Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;

	//Starting packet position thread
	std::thread positionUpdater(udpThread);

	//Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(constants.serverListeningPort);
	selector.add(listener);

	while(true){

		if(selector.wait()){
			if(selector.isReady(listener)){ //If we got no informatino but we got a new connection, make a new client
				Client client;
				listener.accept(*client.socket);
				client.id = createUniqueID();
				clients.push_back(client);
				selector.add(*client.socket);
				std::cout << "New client connected with ID: " << (unsigned int)client.id << std::endl;

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
				client.socket->send(packet);

			}else{ //Otherwise, we got information, so then send that packet we received to all other clients
				for(unsigned int i = 0; i < clients.size(); i++){
					if(selector.isReady(*clients[i].socket)){
						sf::Packet packet;
						sf::Socket::Status status = clients[i].socket->receive(packet);

						if(status == sf::Socket::Done){

							std::cout << "got packet" << std::endl;

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

							for(unsigned int j = 0; j < clients.size(); j++){
								if(i != j){
									clients[j].socket->send(packet);
								}
							}
						}else if(status == sf::Socket::Disconnected){
							std::cout << "Client with id " << (unsigned int)clients[i].id << " disconnected" << std::endl;
							clients[i] = clients.back();
							clients.pop_back();
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

void printConstants(const Constants& constants){
	//Printing the constants for debug
	std::cout << "ChunkWidth: " << constants.chunkWidth << std::endl;
	std::cout << "WorldWidth: " << constants.worldWidth << std::endl;
	std::cout << "WorldHeight: " << constants.worldHeight << std::endl;
	std::cout << "ServerPort: " << constants.serverPort << std::endl;
	std::cout << "ServerListeningPort: " << constants.serverListeningPort << std::endl;
	std::cout << "ClientPort: " << constants.clientPort << std::endl;
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
          }else if(s == "ServerPort:"){
			is >> constants.serverPort;
		}else if(s == "ClientPort:"){
			is >> constants.clientPort;
		}else if(s == "ServerListeningPort:"){
			is >> constants.serverListeningPort;
		}
     }

     is.close();

	return constants;
}

uint8_t createUniqueID(){
	uint8_t id = rand()%256;
	if(!doesIDExist(id)){
		return id;
	}
	return createUniqueID();
}

bool doesIDExist(uint8_t id){
	for(auto& i : clients){
		if(i.id == id) return true;
	}
	return false;
}
