#pragma once

#include "Chunk.hpp"
#include "InputManager.hpp"
#include "Math.hpp"
#include "Config.hpp"


class Camera {
public:

	void init(const Config* _config);

	void calculateCameraVectors(float deltaTime);
	float getPitch() const;
	float getYaw() const;
	const math::mat4& getProjectionMatrix() const;
	const math::mat4& getViewMatrix() const;
	const math::vec3& getPosition() const;
	const math::vec3& getForward() const;
	void setForward(const math::vec3&);
	void setPosition(const math::vec3& vec);
	void updateViewMatrix();


private:

	float m_pitch = 0.0f;
	float m_yaw = 0.0f;
	math::vec3 m_position;
	math::vec3 m_forward;
	math::mat4 m_projectionMatrix;
	math::mat4 m_viewMatrix;


};


