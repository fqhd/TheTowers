#include "EntityHandler.hpp"


void EntityHandler::init() {
	m_entityModel.init("res/models/monkey.obj");
	m_shader.load("res/shaders/entity_vertex_shader.glsl", "res/shaders/entity_fragment_shader.glsl");
}

void EntityHandler::update(float _deltaTime) {
	for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
		it->second.update(_deltaTime);
	}
}

void EntityHandler::addEntity(uint8_t id, const glm::vec3& position, float pitch, float yaw) {
	Entity entity;
	entity.transform.setPosition(position);
	entity.setTargetPosition(position);
	entity.setForward(pitch, yaw);
	m_entities[id] = entity;
}

void EntityHandler::removeEntity(uint8_t id) {
	m_entities.erase(id);
}

void EntityHandler::updateEntity(uint8_t id, const glm::vec3& position, float pitch, float yaw){
	auto it = m_entities.find(id);
	if (it != m_entities.end()) {
		it->second.setTargetPosition(position);
		it->second.setForward(pitch, yaw);
	} else {
		addEntity(id, position, pitch, yaw);
	}
}

void EntityHandler::render(Camera& camera) {
	m_shader.bind();
	m_shader.loadUniform("view", camera.getViewMatrix());
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("camPos", camera.getPosition());
	for(auto it = m_entities.begin(); it != m_entities.end(); it++){
		m_shader.loadUniform("isBlueTeam", it->second.isBlueTeam());
		m_shader.loadUniform("model", it->second.transform.getMatrix());
		m_entityModel.render(); // Change to actual model
	}
	m_shader.unbind();
}

void EntityHandler::destroy(){
	m_entityModel.destroy();
	m_shader.destroy();
}
