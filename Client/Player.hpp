#pragma once
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleRenderer.hpp"

enum Face{
     FACE_0,
     FACE_1,
     FACE_2,
     FACE_3,
     FACE_4,
     FACE_5,

};

class Player {
public:

     void init();
     void update(sf::Window& window, const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, float deltaTime, uint8_t blockID);

	void movement(float deltaTime);
     void calculateCameraVectors(sf::Window& window);
     void breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, uint8_t b);
     Face getFace(float x, float y, float z);

     glm::vec3 position;
     Camera camera;

private:


     float m_speed = 25.5f;

};
