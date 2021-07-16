#include "EntityHandler.hpp"
#include "Engine/Utils/Utils.hpp"


void EntityHandler::init() {
}

void EntityHandler::update(NetworkManager* _manager, float _deltaTime) {
	sf::Packet packet;
	sf::IpAddress remoteIp;
	unsigned short remotePort;

	while (_manager->m_udpSocket.receive(packet, remoteIp, remotePort) == sf::Socket::Done) {
		math::vec3 position;
		float pitch, yaw;
		uint8_t remoteID;

		packet >> remoteID >> position.x >> position.y >> position.z >> pitch >> yaw;

		if (m_entities.find(remoteID) != m_entities.end()) {
			m_entities[remoteID].setTargetPosition(position);
			m_entities[remoteID].setForward(pitch, yaw);
		} else {
			addEntity(remoteID, position, pitch, yaw);
		}
	}

	//Update Entities
	for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
		it -> second.update(_deltaTime);
	}
}

void EntityHandler::addEntity(uint8_t id, const math::vec3& position, float pitch, float yaw) {
	// Entity entity(Transform(math::vec3(0.0f), math::vec3(0.0f), math::vec3(1.0f)));
	Entity entity;
	entity.setTargetPosition(position);
	entity.setForward(pitch, yaw);
	m_entities[id] = entity;
}

void EntityHandler::removeEntity(uint8_t id) {
	m_entities.erase(id);
}

void EntityHandler::render(Camera& camera) {

}

void EntityHandler::destroy(){
	
}
