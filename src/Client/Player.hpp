#pragma once

#include "Camera.hpp"
#include "World.hpp"
#include "ParticleHandler.hpp"
#include "Hotbar.hpp"
#include "AABBox.hpp"
#include "NetworkManager.hpp"
#include "GameMode.hpp"
#include <SFML/Network.hpp>

struct VisibleBlocks {
	math::ivec3 breakableBlock; // The block that the player is looking at
	math::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
	bool lookingAtBlock = false;
	bool isInsideBlock = false;
};



class Player {
public:

	void init(unsigned int _reachDistance);
	void update(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager, float deltaTime);
	void mouseHandler(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager);
	void kbHandler(const Camera& camera, World* world, InputManager* _iManager, float deltaTime);
	math::vec3 getEyePos() const;

	uint8_t selectedBlock = 1;

	VisibleBlocks visibleBlocks;
	Hotbar hotbar;

private:

	void getVisibleBlocks(const Camera& camera, World* world);
	void placeBlock(World* world);
	void breakBlock(ParticleHandler& handler, World* world);
	math::ivec3 vecToBlock(const math::vec3& vec);
	void collideWithWorld(World* _world);
	static bool compareDistance(AABB a, AABB b);

	unsigned int m_reachDistance = 0;
	math::vec3 m_velocity;
	bool m_canJump = false;
	GameMode m_gamemode=GameMode::SPECTATOR;
	float m_health;

};
