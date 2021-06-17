#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <SFML/Network.hpp>
#include "Engine/World/World.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "EntityHandler.hpp"
#include "Engine/Utils/Camera.hpp"

class NetworkManager {
public:

	friend class EntityHandler;

	void connectToServer(sf::IpAddress& _ip);
	void downloadWorld(uint8_t* _data, unsigned int _size);
	void receiveGameUpdatePacket(World& _world, ParticleHandler& _pHandler, EntityHandler& _eHandler);
	void sendPositionDataToServer(Camera& _camera);
	void sendBlockData(const glm::ivec3& _blockPosition, uint8_t _blockType);



private:

	sf::Clock m_dataFrequencyTimer;
	sf::IpAddress m_serverIp;
	sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	uint8_t m_id = 0;

};

#endif