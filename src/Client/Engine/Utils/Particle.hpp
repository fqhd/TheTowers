#pragma once

#include <glm/glm.hpp>
#include "Vertex.hpp"

class Particle {
public:

	Particle(const glm::vec3& position, const glm::vec3& velocity, float lifelength, float rotation, float scale);

	bool update(float deltaTime);

	const glm::vec3& getPosition() const;
	float getRotation() const;
	float getScale() const;
	float getLifeLength() const;
	float getElapsedTime() const;



private:

	glm::vec3 m_position;
	glm::vec3 m_velocity;
	float m_lifeLength = 0.0f;
	float m_rotation = 0.0f;
	float m_scale = 0.0f;
	float m_elapsedTime = 0.0f;

};


