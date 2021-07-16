#pragma once

#include "Engine/Utils/Camera.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "Hotbar.hpp"
#include <SFML/Network.hpp>

struct VisibleBlocks {
	math::ivec3 breakableBlock; // The block that the player is looking at
	math::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
	bool lookingAtBlock = false;
	bool isInsideBlock = false;
};

class Player {
public:

	void update(Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager);

	uint8_t selectedBlock = 1;
	VisibleBlocks visibleBlocks;
	Hotbar hotbar;

private:

	void getVisibleBlocks(Camera& camera, World* world);
	void placeBlock(World* world);
	void breakBlock(ParticleHandler& handler, World* world);
	math::ivec3 vecToBlock(const math::vec3& vec);

};
