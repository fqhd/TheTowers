#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include "Structs.hpp"
#include "Perlin.hpp"


// Forward Declarations
uint8_t createUniqueID();
bool doesIDExist(uint8_t id);
void addClient(sf::TcpListener& listener, sf::SocketSelector& selector);
void udpThread();
void compressAndSendWorld(uint8_t* data);
void freeWorldData(uint8_t* data);
void updateWorldBasedOnPacket(sf::Packet& packet, uint8_t* data);
uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet, unsigned int& _senderIndex);
void sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID);
void sendPacketToAllClients(sf::Packet& packet);
void disconnectPlayer(sf::SocketSelector& _selector, unsigned int _playerID);

// Global Variables
std::vector<Client> clients;
bool isDone = false;

const unsigned int WORLD_WIDTH = 32;
const unsigned int WORLD_HEIGHT = 8;
const unsigned int CHUNK_WIDTH = 32;
const unsigned int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;
const unsigned int CLIENT_PORT = 7459;
const unsigned int SERVER_PORT = 7456;

int main(){
	// Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;

	std::thread positionUpdater(udpThread); // Starting packet position thread

	// Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(SERVER_PORT);
	selector.add(listener);

	while(!isDone){
		if(selector.wait()){ // Wait for event to happen
			if(selector.isReady(listener)){ // Got new connection, so we are going to handle that by creating a new client
				addClient(listener, selector);
			} else { // Got data from a connected client so we are going to send it to all other clients
				sf::Packet receivedPacket;
				unsigned int senderIndex;
				uint8_t code = getReceivedPacket(selector, receivedPacket, senderIndex);
				
				switch(code){
					case 1: // Disconnect
						disconnectPlayer(selector, senderIndex);
					break;
					case 2: // Block Update
						std::cout << "Got block update packet" << std::endl;
						sendPacketToOtherClients(receivedPacket, senderIndex);
					break;
					case 3: // Chunk Request
						std::cout << "Got chunk request packet" << std::endl;
					break;
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

uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet, unsigned int& _senderIndex) {
	for(unsigned int i = 0; i < clients.size(); i++){
		if(selector.isReady(*clients[i].socket)){
			sf::Socket::Status status = clients[i].socket->receive(packet);
			if(status == sf::Socket::Done){ // Got a valid packet
				_senderIndex = i;
				uint8_t code;
				packet >> code;
				return code;
			} else if (status == sf::Socket::Disconnected) { // The client has disconnected
				// We remove the client and send a packet to other clients that a player has disconnected
				_senderIndex = i;
				return 1; // We return 1 because 1 is the code for a disconnect request
			}
		}
	}
	return 0;
}

void disconnectPlayer(sf::SocketSelector& _selector, unsigned int _playerID){
	sf::Packet packet;
	packet.clear();
	packet << (uint8_t)1 << clients[_playerID].id; // We send the keycode 1 because that is the code for a disconnection
	sendPacketToAllClients(packet);
	std::cout << "Client Disconnected with ID: " << (unsigned int)clients[_playerID].id << std::endl;
	_selector.remove(*clients[_playerID].socket);
	delete clients[_playerID].socket;
	clients[_playerID] = clients.back();
	clients.pop_back();
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
