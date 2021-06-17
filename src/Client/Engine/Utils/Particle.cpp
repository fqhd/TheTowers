#include "Particle.hpp"
#include "../../../Constants.hpp"

const float GRAVITY = 12.0f;

Particle::Particle(const glm::vec3 & position, const glm::vec3 & velocity, float lifelength, float rotation, float scale) {
	m_position = position;
	m_velocity = velocity;
	m_lifeLength = lifelength;
	m_rotation = rotation;
	m_scale = scale;
}

const glm::vec3& Particle::getPosition() const {
	return m_position;
}

float Particle::getRotation() const {
	return m_rotation;
}

float Particle::getScale() const {
	return m_scale;
}

float Particle::getLifeLength() const {
	return m_lifeLength;
}

float Particle::getElapsedTime() const {
	return m_elapsedTime;
}

bool Particle::update(float deltaTime) {
	m_velocity.y -= GRAVITY * deltaTime;
	m_position += m_velocity * deltaTime;
	m_elapsedTime += deltaTime;
	return m_elapsedTime > m_lifeLength;
}