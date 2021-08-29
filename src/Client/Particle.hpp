#pragma once

#include "Vertex.hpp"

class Particle {
public:

	Particle(const math::vec3& position, const math::vec3& velocity, float lifelength, float rotation, float scale, unsigned int _index);

	bool update(float deltaTime);

	const math::vec3& getPosition() const;
	float getRotation() const;
	float getScale() const;
	float getLifeLength() const;
	float getElapsedTime() const;
	unsigned int getTextureIndex();



private:

	math::vec3 m_position;
	math::vec3 m_velocity;
	float m_lifeLength;
	float m_rotation;
	float m_scale;
	float m_elapsedTime;
	unsigned int m_index;

};


