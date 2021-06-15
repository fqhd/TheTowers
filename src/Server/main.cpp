#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include "Structs.hpp"
#include "Perlin.hpp"
#include "../Constants.hpp"


// Forward Declarations
uint8_t* generateWorld();
uint8_t createUniqueID();
bool doesIDExist(uint8_t id);
void addClient(sf::TcpListener& listener, sf::SocketSelector& selector);
void udpThread();
void compressAndSendWorld(uint8_t* data);
void freeWorldData(uint8_t* data);
void updateWorldBasedOnPacket(sf::Packet& packet, uint8_t* data);
uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet);
void sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID);
void sendPacketToAllClients(sf::Packet& packet);

// Global Variables
std::vector<Client> clients;
bool isDone = false;

int main(){

	// Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;

	uint8_t* worldData = generateWorld(); // Creating the world data buffer
	std::thread positionUpdater(udpThread); //Starting packet position thread

	// Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(SERVER_PORT);
	selector.add(listener);

	while(!isDone){

		if(selector.wait()){ // Wait for even to happen
			if(selector.isReady(listener)){ // Got new connection, so we are going to handle that by creating a new client

				addClient(listener, selector);
				compressAndSendWorld(worldData);

			}else{ // Got data from a connected client so we are going to send it to all other clients

				sf::Packet receivedPacket;
				uint8_t remoteClientID = getReceivedPacket(selector, receivedPacket);
				if(remoteClientID){
					updateWorldBasedOnPacket(receivedPacket, worldData);
					sendPacketToOtherClients(receivedPacket, remoteClientID);
				}
			}
		}

	}

	positionUpdater.join();


     return 0;
}

void udpThread(){

	//Variables for algorithm
	sf::UdpSocket socket;
	sf::Packet receivedPacket;
	sf::IpAddress remoteIp;
	unsigned short remotePort;

	//Initializing variables
	socket.bind(SERVER_PORT);
	socket.setBlocking(false);

	while(!isDone){
		receivedPacket.clear();

		while(socket.receive(receivedPacket, remoteIp, remotePort) == sf::Socket::Done){

			uint8_t id;
			receivedPacket >> id;
			receivedPacket << id;

			for(auto& i : clients){
				if(i.id != id) socket.send(receivedPacket, i.socket->getRemoteAddress(), CLIENT_PORT);
			}


		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

}

uint8_t* generateWorld(){

	//Allocating memory for world data
	uint8_t* data = (uint8_t*)malloc(WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE);
	std::cout << "World Size(GB): " << (WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE) / 1000000000.0f << std::endl;

	//Generating the world with perlin noise
	Perlin perlin;
	perlin.init(CHUNK_WIDTH * WORLD_WIDTH, 7, 0.3f);
	for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_WIDTH; z++){
		for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_WIDTH; x++){

			unsigned int height = perlin.noise(x, z) * CHUNK_WIDTH * WORLD_HEIGHT;

			for(unsigned int y = 0; y < CHUNK_WIDTH * WORLD_HEIGHT; y++){
				data[(y * CHUNK_WIDTH * WORLD_WIDTH * CHUNK_WIDTH * WORLD_WIDTH) + (z * CHUNK_WIDTH * WORLD_WIDTH) + x] =  0;

				if(y <= height){
					if(y == height){
						if(height > 32){
							data[(y * CHUNK_WIDTH * WORLD_WIDTH * CHUNK_WIDTH * WORLD_WIDTH) + (z * CHUNK_WIDTH * WORLD_WIDTH) + x] =  3;
						}else{
							data[(y * CHUNK_WIDTH * WORLD_WIDTH * CHUNK_WIDTH * WORLD_WIDTH) + (z * CHUNK_WIDTH * WORLD_WIDTH) + x] =  1;
						}
					}else{
						data[(y * CHUNK_WIDTH * WORLD_WIDTH * CHUNK_WIDTH * WORLD_WIDTH) + (z * CHUNK_WIDTH * WORLD_WIDTH) + x] =  4;
					}
				}
				
			}
		}
	}
	perlin.destroy();

	return data;
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

void compressAndSendWorld(uint8_t* data){
	//Compressing the world into a packet
	sf::Packet packet;
	uint32_t numBlocks = 1;
	for(uint32_t i = 1; i < (WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE); i++){
		if(data[i - 1] != data[i]){
			packet << (uint8_t)data[i - 1] << numBlocks;
			numBlocks = 1;
		}else{
			numBlocks++;
		}
	}
	packet << (uint8_t)data[WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE - 1] << numBlocks;

	//Sending the packet containing the compressed world to the newly connected client
	clients.back().socket->send(packet);

}

void updateWorldBasedOnPacket(sf::Packet& packet, uint8_t* data){

	//Variables for received packet information
	int x;
	int y;
	int z;
	uint8_t b;
	uint8_t code;

	//Depackaging packet
	packet >> code >> x >> y >> z >> b;

	x = x % (WORLD_WIDTH * CHUNK_WIDTH);
	y = y % (WORLD_HEIGHT * CHUNK_WIDTH);
	z = z % (WORLD_WIDTH * CHUNK_WIDTH);

	//Updating world data based on sent packet
	if(!(x < 0 || x >= CHUNK_WIDTH * WORLD_WIDTH || y < 0 || y >= CHUNK_WIDTH * WORLD_HEIGHT || z < 0 || z >= CHUNK_WIDTH * WORLD_WIDTH)){
		data[(y * CHUNK_WIDTH * WORLD_WIDTH * CHUNK_WIDTH * WORLD_WIDTH) + (z * CHUNK_WIDTH * WORLD_WIDTH) + x] = b;
	}

	//Repackaging packet
	packet << code << x << y << z << b;
}

uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet){
	for(unsigned int i = 0; i < clients.size(); i++){
		if(selector.isReady(*clients[i].socket)){
			sf::Socket::Status status = clients[i].socket->receive(packet);

			if(status == sf::Socket::Done){ // Got a valid packet
				return clients[i].id;
			}else if(status == sf::Socket::Disconnected){ // The client has disconnected

				packet.clear();
				packet << (uint8_t)1 << clients[i].id; // We send the keycode 1 because that is the code for a disconnection
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
