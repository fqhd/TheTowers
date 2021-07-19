#pragma once

#include "Engine/Utils/Camera.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "Hotbar.hpp"
#include <SFML/Network.hpp>

#define PLAYER_WIDTH 0.5f
#define PLAYER_DEPTH PLAYER_WIDTH
#define PLAYER_HEIGHT 2.0f
#define AIR_FRICTION 0.95f
#define SPEED 2.0f

struct VisibleBlocks {
	math::ivec3 breakableBlock; // The block that the player is looking at
	math::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
	bool lookingAtBlock = false;
	bool isInsideBlock = false;
};

class Player {
public:
	Player();
	void update(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager, float deltaTime);
	void mouseHandler(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager);
	void kbHandler(const Camera& camera, World* world, InputManager* _iManager, float deltaTime);
	void init();
	math::vec3 getEyePos();
	uint8_t selectedBlock = 1;
	VisibleBlocks visibleBlocks;
	Hotbar hotbar;

private:

	void getVisibleBlocks(const Camera& camera, World* world);
	void placeBlock(World* world);
	void breakBlock(ParticleHandler& handler, World* world);
	float applyDirection(float x1, float x2, float speed, float deltaTime); // returns x1+x2*speed*deltatime
	math::vec3 applyDirections(math::vec3 v1, math::vec3 v2, float speed, float deltaTime); // same as applyDirection but with vectors
	math::ivec3 vecToBlock(const math::vec3& vec);
	math::vec4 m_velocites;
	float dy; // dy velocity
	math::vec3 position;

};
