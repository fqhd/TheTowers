#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include "Structs.hpp"
#include "Perlin.hpp"


//Forward Declarations
Constants getConstants();
uint8_t* generateWorld(const Constants& constants);
void printConstants(const Constants& constants);
uint8_t createUniqueID();
bool doesIDExist(uint8_t id);
void addClient(sf::TcpListener& listener, sf::SocketSelector& selector);
void udpThread();
void compressAndSendWorld(uint8_t* data, const Constants& constants);
void freeWorldData(uint8_t* data);
void updateWorldBasedOnPacket(const Constants& constants, sf::Packet& packet, uint8_t* data);
uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet);
void sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID);
void sendPacketToAllClients(sf::Packet& packet);

//Global Variables
std::vector<Client> clients;
bool isDone = false;

int main(){

	//Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;

	Constants constants = getConstants(); // Getting the constant values for synced client/server interaction
	printConstants(constants); // Printing the constants
	uint8_t* worldData = generateWorld(constants); // Creating the world data buffer
	std::thread positionUpdater(udpThread); //Starting packet position thread

	//Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(constants.serverListeningPort);
	selector.add(listener);

	while(!isDone){

		if(selector.wait()){ // Wait for even to happen
			if(selector.isReady(listener)){ // Got new connection, so we are going to handle that by creating a new client

				addClient(listener, selector);
				compressAndSendWorld(worldData, constants);

			}else{ // Got data from a connected client so we are going to send it to all other clients

				sf::Packet receivedPacket;
				uint8_t remoteClientID = getReceivedPacket(selector, receivedPacket);
				if(remoteClientID){
					updateWorldBasedOnPacket(constants, receivedPacket, worldData);
					sendPacketToOtherClients(receivedPacket, remoteClientID);
				}
			}
		}

	}

	positionUpdater.join();


     return 0;
}

void udpThread(){

	// Getting constants
	Constants constants = getConstants();

	//Variables for algorithm
	sf::UdpSocket socket;
	sf::Packet receivedPacket;
	sf::IpAddress remoteIp;
	unsigned short remotePort;

	//Initializing variables
	socket.bind(constants.serverPort);
	socket.setBlocking(false);

	while(!isDone){
		receivedPacket.clear();

		while(socket.receive(receivedPacket, remoteIp, remotePort) == sf::Socket::Done){

			uint8_t id;
			receivedPacket >> id;
			receivedPacket << id;

			for(auto& i : clients){
				if(i.id != id) socket.send(receivedPacket, i.socket->getRemoteAddress(), constants.clientPort);
			}


		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}


}

uint8_t* generateWorld(const Constants& constants){
	unsigned int ww = constants.worldWidth;
	unsigned int wh = constants.worldHeight;
	unsigned int cw = constants.chunkWidth;
	unsigned int cs = cw * cw * cw;

	//Allocating memory for world data
	uint8_t* data = (uint8_t*)malloc(ww * ww * wh * cs);
	std::cout << "World Size(bytes): " << ww * ww * wh * cs << std::endl;

	//Generating the world with perlin noise
	Perlin perlin;
	perlin.init(cw * ww, 6, 0.5f);
	for(unsigned int z = 0; z < cw * ww; z++){
		for(unsigned int x = 0; x < cw * ww; x++){

			unsigned int height = perlin.noise(x, z) * cw * wh;

			for(unsigned int y = 0; y < cw * wh; y++){
				data[(y * cw * ww * cw * ww) + (z * cw * ww) + x] = y < height ? y + 100 : 0;
			}

		}
	}
	perlin.destroy();

	return data;
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
	uint8_t id = rand()%255 + 1;
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

void addClient(sf::TcpListener& listener, sf::SocketSelector& selector) {
	// Adding new client to list of clients
	Client client;
	listener.accept(*client.socket);
	client.id = createUniqueID();
	clients.push_back(client);
	selector.add(*client.socket);

	// Sending chosen ID to client
	sf::Packet packet;
	packet << client.id;
	client.socket->send(packet);
	packet.clear();
	std::cout << "New client connected with ID: " << (unsigned int)client.id << std::endl;
}

void freeWorldData(uint8_t* data){
	free(data);
}

void compressAndSendWorld(uint8_t* data, const Constants& constants){

	unsigned int ww = constants.worldWidth;
	unsigned int wh = constants.worldHeight;
	unsigned int cw = constants.chunkWidth;
	unsigned int cs = cw * cw * cw;

	//Compressing the world into a packet
	sf::Packet packet;
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

	//Sending the packet containing the compressed world to the newly connected client
	clients.back().socket->send(packet);

}

void updateWorldBasedOnPacket(const Constants& constants, sf::Packet& packet, uint8_t* data){

	unsigned int ww = constants.worldWidth;
	unsigned int wh = constants.worldHeight;
	unsigned int cw = constants.chunkWidth;
	unsigned int cs = cw * cw * cw;

	//Variables for received packet information
	int x;
	int y;
	int z;
	uint8_t b;

	//Depackaging packet
	packet >> x >> y >> z >> b;

	x = x % (ww * cw);
	y = y % (wh * cw);
	z = z % (ww * cw);

	//Updating world data based on sent packet
	if(!(x < 0 || x >= cw * ww || y < 0 || y >= cw * wh || z < 0 || z >= cw * ww)){
		data[(y * cw * ww * cw * ww) + (z * cw * ww) + x] = b;
	}

	//Repackaging packet
	packet << x << y << z << b;
}

uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet){
	for(unsigned int i = 0; i < clients.size(); i++){
		if(selector.isReady(*clients[i].socket)){
			sf::Socket::Status status = clients[i].socket->receive(packet);

			if(status == sf::Socket::Done){ // Got a valid packet
				return clients[i].id;
			}else if(status == sf::Socket::Disconnected){ // The client has disconnected

				packet.clear();
				packet << (uint8_t)8 << clients[i].id;
				sendPacketToAllClients(packet);


				std::cout << "Client Disconnected with ID: " << (unsigned int)clients[i].id << std::endl;
				selector.remove(*clients[i].socket);
				delete clients[i].socket;
				clients[i] = clients.back();
				clients.pop_back();
				return 0;
			}


		}
	}
	return 0;
}

void sendPacketToAllClients(sf::Packet& packet){
	for(auto& i : clients){
		i.socket->send(packet);
	}
}

void sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID){
	for(auto& i : clients){
		if(i.id != senderID) i.socket->send(packet);
	}
}
