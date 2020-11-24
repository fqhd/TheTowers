#pragma once
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleRenderer.hpp"
#include "Settings.hpp"
#include <SFML/Network.hpp>

class Player {
public:

     void init();
     void update(sf::Window& window, const Settings& settings, const std::vector<vec3>& colors, ParticleRenderer& renderer,
          InputManager& manager, World& world, float deltaTime, uint8_t blockID, sf::TcpSocket& socket);

	void movement(float deltaTime, const Settings& settings, InputManager& manager);
     void calculateCameraVectors(sf::Window& window, float sensibility);
     void breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, uint8_t b, sf::TcpSocket& socket);

     glm::vec3 position;
     Camera camera;

private:



};
