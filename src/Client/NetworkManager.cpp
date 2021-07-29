#include "NetworkManager.hpp"
#include <iostream>

void NetworkManager::connectToServer(sf::IpAddress& _ip, Config* _c){
	m_config = _c;
	m_serverIp = _ip;
	m_udpSocket.bind(m_config->getClientPort());
	m_udpSocket.setBlocking(false);

	// Connecting to server
	std::cout << "Connecting..." << std::endl;
	if (m_tcpSocket.connect(m_serverIp, m_config->getServerPort()) == sf::Socket::Status::Done) {
		std::cout << "Connected to server!" << std::endl;
		sf::Packet packet;
		m_tcpSocket.setBlocking(true);
		if(m_tcpSocket.receive(packet) != sf::Socket::Status::Done){
			std::cout << "Failed to receive packet from server" << std::endl;
			return;
		}
		m_tcpSocket.setBlocking(false);
		packet >> m_id;
		std::cout << "Connected to server with ID: " << (unsigned int)m_id << std::endl;
	} else {
		std::cout << "Failed to connect to server" << std::endl;
	}
}

sf::Socket::Status NetworkManager::receiveGameUpdatePacket(sf::Packet& _packet){
	return m_tcpSocket.receive(_packet);
}

sf::Socket::Status NetworkManager::receiveEntityUpdatePacket(sf::Packet& _packet){
	sf::IpAddress remoteIp;
	unsigned short remotePort;
	return m_udpSocket.receive(_packet, remoteIp, remotePort);
}


void NetworkManager::sendPositionDataToServer(Camera& _camera){
	// We execute this code only a few times per second
	// This code sends the position and camera angles to the server
	// Which will in turn send it to other connected clients except ourselves
	sf::Packet packet;
	math::vec3 p = _camera.getPosition(); // Camera Position
	packet << m_id << p.x << p.y << p.z << _camera.getPitch() << _camera.getYaw();
	m_udpSocket.send(packet, m_serverIp, m_config->getServerPort());
}

void NetworkManager::sendBlockUpdatePacket(const math::ivec3& _blockPosition, uint8_t _blockType){
	sf::Packet packet;
	packet << (uint8_t)2 << _blockPosition.x << _blockPosition.y << _blockPosition.z << _blockType; // We send the keycode 2 because that is the code for a block update.
	m_tcpSocket.send(packet);
}
