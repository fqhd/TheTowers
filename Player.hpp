#pragma once
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleRenderer.hpp"

class Player {
public:

     void init();
     void update(sf::Window& window, const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, float deltaTime, uint8_t blockID);

	void movement(float deltaTime);
     void calculateCameraVectors(sf::Window& window);
     void breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, uint8_t b);

     glm::vec3 position;
     Camera camera;

private:


     float m_speed = 5.5f;

};
