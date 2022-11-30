#pragma once

#include "Camera.hpp"
#include "World.hpp"
#include "ParticleHandler.hpp"
#include "Hotbar.hpp"
#include "AABBox.hpp"
#include "NetworkManager.hpp"
#include "GameMode.hpp"
#include "Item.hpp"
#include "Hotbar.hpp"
#include "Converter.hpp"

struct VisibleBlocks {
	glm::ivec3 breakableBlock; // The block that the player is looking at
	glm::ivec3 placeableBlock; // The position of the potential block placement. If a player right clicks, a block will be placed at this position
	bool lookingAtBlock = false;
};


class Player {
public:

	void init(Camera* _camera, ParticleHandler* _handler, World* _world, NetworkManager* _nMangaer);
	void update(float deltaTime);
	void placeAndBreakBlocks();
	void movement(float deltaTime);
	glm::vec3 getEyePos() const;

	VisibleBlocks visibleBlocks;
	Hotbar hotbar;
	GameMode gamemode = SPECTATOR;

private:

	void getVisibleBlocks();
	void placeBlock();
	void breakBlock();
	void collideWithWorld();
	static bool compareDistance(AABB a, AABB b);
	bool canPlaceBlock();

	bool m_canJump = false;
	float m_yVelocity = 0.0f;

	// Pointers
	NetworkManager* m_networkManager = nullptr;
	ParticleHandler* m_particleHandler = nullptr;
	World* m_world = nullptr;
	Camera* m_camera = nullptr;
	
};
