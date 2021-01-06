#ifndef CAMERA_H
#define CAMERA_H
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Chunk.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"


class Plane {
public:
	void setNormalAndPoint(const glm::vec3& normal, const glm::vec3& point){
		n = normal;
		d = point;
	}
	glm::vec3 n, d;
};

class Camera {
public:

	void init();
	void update(Settings& settings, float deltaTime);
	void updateProjectionMatrix();
	bool isInView(const glm::vec3& position, float radius);


	const glm::mat4& getProjectionMatrix();
	const glm::mat4& getViewMatrix();
	const glm::vec3& getPosition();
	const glm::vec3& getForward();



private:

	Plane pl[6];

	//Private Functions
	void calculateCameraVectors(float deltaTime);
	void movement(float deltaTime, Settings& settings);
	void updateViewMatrix();

	float m_pitch = 0.0f;
	float m_yaw = 90.0f;
	glm::vec3 m_forward;
	glm::vec3 m_position;


	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;


};

#endif
