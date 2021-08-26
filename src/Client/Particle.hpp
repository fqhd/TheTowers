#pragma once

#include "Vertex.hpp"
#include "TextureIndex.hpp"

class Particle {
public:

	Particle(const math::vec3& position, const math::vec3& velocity, float lifelength, float rotation, float scale, TextureIndex _index);

	bool update(float deltaTime);

	const math::vec3& getPosition() const;
	float getRotation() const;
	float getScale() const;
	float getLifeLength() const;
	float getElapsedTime() const;
	TextureIndex getTextureIndex();



private:

	math::vec3 m_position;
	math::vec3 m_velocity;
	float m_lifeLength = 0.0f;
	float m_rotation = 0.0f;
	float m_scale = 0.0f;
	float m_elapsedTime = 0.0f;
	TextureIndex m_index;

};


