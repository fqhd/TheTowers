#include "NetworkManager.hpp"
#include <iostream>

const unsigned int CLIENT_PORT = 7459;
const unsigned int SERVER_PORT = 7456;
const unsigned int PACKET_TRANSMISSION_FREQUENCY = 10;

void NetworkManager::connectToServer(sf::IpAddress& _ip){
	m_serverIp = _ip;

	m_udpSocket.bind(CLIENT_PORT);
	m_udpSocket.setBlocking(false);

	std::cout << "Connecting..." << std::endl;
	sf::Socket::Status status = m_tcpSocket.connect(m_serverIp, SERVER_PORT);

	if (status != sf::Socket::Status::Done) {
		Utils::log("Game: Failed to connect to server");
	} else {
		sf::Packet packet;
		m_tcpSocket.setBlocking(true);
		m_tcpSocket.receive(packet);
		m_tcpSocket.setBlocking(false);
		packet >> m_id;
		Utils::log("Game: Connected to server with ID: " + std::to_string(m_id));
	}

}

void NetworkManager::downloadWorld(uint8_t* _data, unsigned int _size){
	// Allocating memory for the world

	sf::Packet packet;

	// Receiving the world in a packet
	m_tcpSocket.setBlocking(true);
	m_tcpSocket.receive(packet);
	m_tcpSocket.setBlocking(false);

	// Printing information
	std::cout << "Received Packet Size: " + std::to_string(packet.getDataSize()) << " bytes" << std::endl;
	std::cout << "World Compression Ratio: " + std::to_string((1.0f - packet.getDataSize() / (float)_size) * 100.0f) << std::endl;

	uint8_t blockID = 0;
	uint32_t pointer = 0;
	uint32_t numBlocks = 0;
	while (packet >> blockID) {
		packet >> numBlocks;
		for (uint32_t i = 0; i < numBlocks; i++) {
			_data[pointer + i] = blockID;
		}
		pointer += numBlocks;
	}

}

void NetworkManager::receiveGameUpdatePacket(World& _world, ParticleHandler& _pHandler, EntityHandler& _eHandler){
	sf::Packet packet;

	if (m_tcpSocket.receive(packet) == sf::Socket::Done) {

		uint8_t code = 0;

		packet >> code;
		if (code == 0) { // If the code is 0 then it is a block update packet
			int x = 0;
			int y = 0;
			int z = 0;
			uint8_t b = 0;

			packet >> x >> y >> z >> b;

			std::cout << "Got block update" << std::endl;

			if (!b) {
				_pHandler.placeParticlesAroundBlock(x, y, z);
			}
			_world.setBlock(x, y, z, b);
		} else if (code == 1) { // If the code is not 0 then a client has disconnected
			uint8_t id = 0;
			packet >> id;
			std::cout << "Person: " + std::to_string(id) + " has disconnected" << std::endl;
			_eHandler.removeEntity(id);
		}

	}
}

void NetworkManager::sendPositionDataToServer(Camera& _camera){
	float timeBetweenPackets = 1.0f / PACKET_TRANSMISSION_FREQUENCY;
	if (m_dataFrequencyTimer.getElapsedTime().asSeconds() >= timeBetweenPackets) {
		m_dataFrequencyTimer.restart();

		// We execute this code only a few times per second
		// This code sends the position and camera angles to the server
		// Which will in turn send it to other connected clients except ourselves
		sf::Packet packet;
		glm::vec3 p = _camera.getPosition(); // Camera Position
		packet << m_id << p.x << p.y << p.z << _camera.getPitch() << _camera.getYaw();
		m_udpSocket.send(packet, m_serverIp, SERVER_PORT);
	}
}

void NetworkManager::sendBlockData(const glm::ivec3& _blockPosition, uint8_t _blockType){
	sf::Packet packet;
	packet << (uint8_t) 0 << _blockPosition.x << _blockPosition.y << _blockPosition.z << _blockType; // We send the keycode 0 because that is the code for a block update.
	m_tcpSocket.send(packet);
}