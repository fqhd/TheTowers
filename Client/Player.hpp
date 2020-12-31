#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleRenderer.hpp"
#include "Settings.hpp"
#include <SFML/Network.hpp>

class Player {
public:

     void update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, sf::TcpSocket& socket);


     uint8_t selectedBlock = 215;

private:

     void breakBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket);
     void placeBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket);

};

#endif
