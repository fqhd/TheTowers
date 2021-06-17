#ifndef PLAYER_H
#define PLAYER_H
#include "Engine/Utils/Camera.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include <SFML/Network.hpp>

struct VisibleBlocks {
	glm::ivec3 breakableBlock; // The block that the player is looking at
	glm::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
	bool lookingAtBlock = false;
	bool isInsideBlock = false;
};

class Player {
public:

	void update(Camera& camera, ParticleHandler& handler, World& world, NetworkManager& _nManager, InputManager* _iManager);

	uint8_t selectedBlock = 215;
	VisibleBlocks visibleBlocks;

private:

	void getVisibleBlocks(Camera& camera, World& world);
	void placeBlock(World& world);
	void breakBlock(ParticleHandler& handler, World& world);
	glm::ivec3 vecToBlock(const glm::vec3& vector);

};

#endif
