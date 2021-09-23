#include "PacketHandler.hpp"


void PacketHandler::init(NetworkManager* _manager, World* _world, ParticleHandler* _pHandler, EntityHandler* _eHandler){
	m_networkManager = _manager;
	m_world = _world;
	m_particleHandler = _pHandler;
	m_entityHandler = _eHandler;
}

void PacketHandler::handlePackets(){
	sf::Packet packet;
	// Receiving the TCP packets
	while(m_networkManager->receiveGameUpdatePacket(packet) == sf::Socket::Status::Done){
		// Getting packet operation code
		uint8_t code;
		packet >> code;
		// Doing different operations based on the packet code
		if(code == 1){ // A Player has Disconnected
			uint8_t id;
			packet >> id;
			std::cout << "Player: " + std::to_string(id) + " has disconnected" << std::endl;
			m_entityHandler->removeEntity(id);
		} else if (code == 2){ // Block Update
			int x = 0;
			int y = 0;
			int z = 0;
			uint8_t b = 0;
			packet >> x >> y >> z >> b;
			if (!b) {
				m_particleHandler->placeParticlesAroundBlock(x, y, z, m_world->getBlock(x, y, z));
			}
			m_world->setBlock(x, y, z, b);
		} else if (code == 3) { // Load map
			uint8_t mapType;
			packet >> mapType;
			if(mapType == 0){ // load the lobby map
				m_world->loadWorldFromFile("lobby.dat");
			} else if (mapType == 1){ // Load the game map
				m_world->loadWorldFromFile("map.dat");
			}
		}
	}

	// Receiving the UDP packets
	while(m_networkManager->receiveEntityUpdatePacket(packet) == sf::Socket::Status::Done){
		math::vec3 position;
		float pitch, yaw;
		uint8_t remoteID;
		packet >> remoteID >> position.x >> position.y >> position.z >> pitch >> yaw;
		m_entityHandler->updateEntity(remoteID, position, pitch, yaw);
	}
}