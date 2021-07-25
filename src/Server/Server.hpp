#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Network.hpp>
#include "Config.hpp"
#include "Structs.hpp"


class Server {

public:
	void start();	
private:
	// private members
	uint8_t* m_worldData = nullptr;
	std::vector<Client> m_clients;
	Config m_config;
	bool m_isDone = false;
	
	//private functions
	uint8_t createUniqueID();
	bool doesIDExist(uint8_t id);
	void addClient(sf::TcpListener& listener, sf::SocketSelector& selector);
	void udpThread();
	void tcpThread();
	void freeWorldData();
	uint8_t getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet, unsigned int& _senderIndex);
	void sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID);
	void sendPacketToAllClients(sf::Packet& packet);
	void disconnectPlayer(sf::SocketSelector& _selector, unsigned int _playerID);
	void generateWorld();
	void setBlock(int _x, int _y, int _z, uint8_t _block);
	void updateWorldWithBlockUpdatePacket(sf::Packet& _packet);
	void addCodeToBlockUpdatePacket(sf::Packet& _packet);
};