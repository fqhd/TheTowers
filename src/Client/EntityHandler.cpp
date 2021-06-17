#include "EntityHandler.hpp"
#include "Engine/Utils/Utils.hpp"


void EntityHandler::init() {
	//Connecting to server?
	m_shader.init();
	m_model.loadFromFile("res/models/suzane.obj");

}

void EntityHandler::update(NetworkManager& _manager, float _deltaTime) {
	sf::Packet packet;
	sf::IpAddress remoteIp;
	unsigned short remotePort;


	while (_manager.m_udpSocket.receive(packet, remoteIp, remotePort) == sf::Socket::Done) {
		glm::vec3 position;
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

void EntityHandler::addEntity(uint8_t id,
	const glm::vec3 & position, float pitch, float yaw) {
	Entity entity(Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
	entity.setTargetPosition(position);
	entity.setForward(pitch, yaw);
	m_entities[id] = entity;
}

void EntityHandler::removeEntity(uint8_t id) {
	m_entities.erase(id);
}

void EntityHandler::render(Camera& camera) {

	m_shader.bind();

	m_shader.loadViewMatrix(camera.getViewMatrix());
	m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_shader.loadLightDirection(camera.getForward());

	for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
		m_shader.loadModelMatrix(it -> second.transform.getMatrix());

		m_model.render();

	}

	m_shader.unbind();

}

void EntityHandler::destroy() {
	m_model.destroy();
	m_shader.destroy();
}
