#include "EntityHandler.hpp"


void EntityHandler::init(Assets* _assets) {
	m_assets = _assets;
	m_shader.init();
}

void EntityHandler::update(NetworkManager* _manager, float _deltaTime) {
	sf::Packet packet;
	sf::IpAddress remoteIp;
	unsigned short remotePort;
	t.setPosition(math::vec3(0, 32, 0));
	t.setRotation(math::vec3(45, 45, 45));
	t.setScale(math::vec3(4, 4, 4));

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
	m_shader.bind();
	m_shader.loadModelMatrix(t.getMatrix());
	m_shader.loadViewMatrix(camera.getViewMatrix());
	m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_assets->getCube().render(0, 6);
	m_shader.unbind();
	// std::unordered_map<uint8_t, Entity>::iterator it;
	// for(it = m_entites.begin(); it != m_entities.end(); it++){
	// 	it->second.
	// }
}

void EntityHandler::destroy(){
	m_shader.destroy();
}
