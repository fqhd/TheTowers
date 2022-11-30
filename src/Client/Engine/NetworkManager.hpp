#pragma once

#include "ParticleHandler.hpp"
#include "Camera.hpp"
#include "Config.hpp"

class NetworkManager {
public:

	/*
	void connectToServer(const sf::IpAddress& _ip, Config* _c);
	sf::Socket::Status receiveGameUpdatePacket(sf::Packet& _packet);
	sf::Socket::Status receiveEntityUpdatePacket(sf::Packet& _packet);
	void sendPositionDataToServer(Camera& _camera);
	void sendBlockUpdatePacket(const math::ivec3& _blockPosition, uint8_t _blockType);
	*/

private:

	/*
	sf::IpAddress m_serverIp;
	sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	*/
	uint8_t m_id = 0;
	Config* m_config = nullptr;

};
