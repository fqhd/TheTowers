#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "Chunk.hpp"
#include "InputManager.hpp"


class Camera {
public:

	friend class Player;

	void init(const glm::vec3& pos);
	void update(sf::Window& window);

	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getViewMatrix() const;
	const glm::vec3& getPosition() const;



private:



	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	glm::vec3 m_position;
	glm::vec3 m_forward;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;


};
