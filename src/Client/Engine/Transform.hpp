#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:

	Transform();

	void setPosition(const glm::vec3& _position);
	void setRotation(const glm::vec3& _rotation);
	void setScale(const glm::vec3& _scale);

	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const glm::vec3& getScale() const;

	void move(const glm::vec3& _delta);

	glm::mat4 getMatrix() const;

private:

	bool m_needsUpdate = true;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_matrix;

};