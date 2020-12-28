#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleRenderer.hpp"
#include "Settings.hpp"
#include <SFML/Network.hpp>

class Player {
public:

     void init();
     void update(const Settings& settings, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, uint8_t blockID, sf::TcpSocket& socket);

	void movement(float deltaTime, const Settings& settings);
     void calculateCameraVectors(float sensibility);
     void breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, uint8_t b, sf::TcpSocket& socket);

     glm::vec3 position;
     Camera camera;

private:



};

#endif
