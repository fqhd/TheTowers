#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.hpp"
#include "World.hpp"
#include "ParticleHandler.hpp"
#include "Settings.hpp"
#include <SFML/Network.hpp>

struct VisibleBlocks {
  glm::ivec3 breakableBlock; // The block that the player is looking at
  glm::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
  bool lookingAtBlock = false;
	bool isInsideBlock = false;
};

class Player {
public:

  void update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleHandler& handler, World& world, float deltaTime, sf::TcpSocket& socket);

  uint8_t selectedBlock = 215;
  VisibleBlocks visibleBlocks;

private:

  void getVisibleBlocks(Camera& camera, World& world);
  void placeBlock(World& world);
  void breakBlock(ParticleHandler& handler, std::vector<vec3>& colors, World& world);
  void sendBlockData(const glm::ivec3& blockUpdate, uint8_t block, sf::TcpSocket& socket);
	glm::ivec3 vecToBlock(const glm::vec3& vector);

};

#endif
