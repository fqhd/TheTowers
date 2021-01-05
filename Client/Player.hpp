#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleHandler.hpp"
#include "Settings.hpp"
#include <SFML/Network.hpp>

struct VisibleBlocks {
     glm::uvec3 breakableBlock;
     glm::uvec3 placeableBlock;
};

class Player {
public:

     void update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleHandler& handler, World& world, float deltaTime, sf::TcpSocket& socket);


     uint8_t selectedBlock = 215;

private:

     VisibleBlocks getVisibleBlocks(Camera& camera, World& world);
     void placeBlock(const VisibleBlocks& visibleBlocks, World& world);
     void breakBlock(const VisibleBlocks& visibleBlocks, ParticleHandler& handler, std::vector<vec3>& colors, World& world);
     void sendBlockData(const glm::uvec3& blockUpdate, uint8_t block, sf::TcpSocket& socket);

};

#endif
