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
     void update(Settings& settings, std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, sf::TcpSocket& socket);

     void breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket);
     void placeBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket);
     Camera camera;
     uint8_t selectedBlock = 0;

private:


};

#endif
