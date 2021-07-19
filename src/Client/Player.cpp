#include "Player.hpp"
#include "Engine/Utils/Utils.hpp"
#include <iostream>

const unsigned int PRECISION = 50;

Player::Player() {
	init();
}

void Player::init() {
	// x = forward, y = -forward, z = side, w = -side
	m_velocites = math::vec4(0.0f);
	dy = 0.0f;
}

void Player::update(Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager, float deltaTime) {
	camera.update();
	mouseHandler(camera, handler, world, _nManager, _iManager);
	kbHandler(camera, world, _iManager, deltaTime);
}	

void Player::mouseHandler(Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager) {
	getVisibleBlocks(camera, world);

	if (!visibleBlocks.lookingAtBlock) return;
	if (visibleBlocks.isInsideBlock) return;

	if (_iManager->isButtonPressed(sf::Mouse::Left)) {
		breakBlock(handler, world);
		_nManager->sendBlockUpdatePacket(visibleBlocks.breakableBlock, 0);
	} else if (_iManager->isButtonPressed(sf::Mouse::Right)) {
		placeBlock(world);
		_nManager->sendBlockUpdatePacket(visibleBlocks.placeableBlock, selectedBlock);
	}

	//We get the visible blocks again to update them after a block has been pressed
	getVisibleBlocks(camera, world);
}


void Player::kbHandler(Camera& camera, World* world, InputManager* _iManager, float deltaTime) {

	if (_iManager->isKeyDown(sf::Keyboard::W)) {
		m_velocites.x += SPEED;
	}

	if (_iManager->isKeyDown(sf::Keyboard::S)) {
		m_velocites.y += SPEED;
	}

	if (_iManager->isKeyDown(sf::Keyboard::A)) {
		m_velocites.z += SPEED;
	}

	if (_iManager->isKeyDown(sf::Keyboard::D)) {
		m_velocites.w += SPEED;
	}

	if (_iManager->isKeyDown(sf::Keyboard::LShift)) {
		dy -= SPEED;
	}

	if (_iManager->isKeyDown(sf::Keyboard::Space)) {
		dy += SPEED;
	}
	
	math::vec3 camForward = camera.getForward();
	math::vec3 forward = math::normalize(math::vec3(camForward.x, 0.0f, camForward.z));
	math::vec3 side = math::normalize(math::cross(camForward, math::vec3(0.0f, 1.0f, 0.0f)));

	math::vec3 camPos = camera.getPosition();
	camPos += forward * m_velocites.x * deltaTime;
	camPos -= forward * m_velocites.y * deltaTime;
	camPos -= side * m_velocites.z * deltaTime;
	camPos += side * m_velocites.w * deltaTime;
	camPos.y += dy * deltaTime;

	m_velocites *= AIR_FRICTION;
	dy *= AIR_FRICTION;
	
	camera.setPosition(camPos);
	camera.setForward(forward);

}


void Player::getVisibleBlocks(Camera& camera, World* world) {
	math::ivec3 pos = vecToBlock(camera.getPosition());
	visibleBlocks.lookingAtBlock = false;
	visibleBlocks.isInsideBlock = world->getBlock(pos.x, pos.y, pos.z) ? true : false;

	float player_reach_distance = world->getPlayerReach();
	math::vec3 rayPosition = camera.getPosition();
	for (unsigned int i = 0; i < PRECISION; i++) {
		rayPosition += camera.getForward() * player_reach_distance / (float)PRECISION;

		visibleBlocks.breakableBlock = vecToBlock(rayPosition);
		uint8_t blockID = world->getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);

		if (blockID) {
			visibleBlocks.lookingAtBlock = true;
			rayPosition -= camera.getForward() * player_reach_distance / (float)PRECISION;
			visibleBlocks.placeableBlock = vecToBlock(rayPosition);
			break;
		}
	}
}

void Player::placeBlock(World* world) {
	world->setBlock(visibleBlocks.placeableBlock.x, visibleBlocks.placeableBlock.y, visibleBlocks.placeableBlock.z, selectedBlock);
}

void Player::breakBlock(ParticleHandler& handler, World* world) {
	// uint8_t blockID = world->getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
	world->setBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z, 0);
	// handler.placeParticlesAroundBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
}

math::ivec3 Player::vecToBlock(const math::vec3& vec) {
	return math::ivec3(math::floor(vec.x), math::floor(vec.y), math::floor(vec.z));
}

// returns x1+x2*speed*deltatime
float Player::applyDirection(float x1, float x2, float speed, float deltaTime) {
	return x1+x2*speed*deltaTime;
}

math::vec3 Player::applyDirections(math::vec3 v1, math::vec3 v2, float speed, float deltaTime) {
	return v1+v2*speed*deltaTime;
}