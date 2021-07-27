#include "Player.hpp"
#include "Utils.hpp"
#include <iostream>

const unsigned int PRECISION = 50;
const float SPEED = 1.25f;
const float PLAYER_WIDTH = 1.0f;
const float PLAYER_HEIGHT = 2.0f;
const float VERTICAL_DRAG = 0.98f;
const float HORIZONTAL_DRAG = 0.8f;
const float GRAVITY = 0.4f;
const float START_HEALTH = 10.0f;

math::vec3 position; // We declare the player position as a global variable because we want to use it in the AABB sorting function

void Player::init(unsigned int _reachDistance) {
	m_reachDistance = _reachDistance;
	position = math::vec3(32, 32, 32);
	m_velocity = math::vec3(0, 0, 0);
	m_health = START_HEALTH;
}

void Player::update(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager, float deltaTime) {
	kbHandler(camera, world, _iManager, deltaTime);
	if (m_gamemode != GameMode::SPECTATOR) collideWithWorld(world);
	mouseHandler(camera, handler, world, _nManager, _iManager);
}

void Player::mouseHandler(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager) {
	getVisibleBlocks(camera, world);

	if (!visibleBlocks.lookingAtBlock) return;
	if (visibleBlocks.isInsideBlock) return;

	if (_iManager->isButtonPressed(sf::Mouse::Left) && m_gamemode != GameMode::ADVENTURE) {
		breakBlock(handler, world);
		_nManager->sendBlockUpdatePacket(visibleBlocks.breakableBlock, 0);
	} else if (_iManager->isButtonPressed(sf::Mouse::Right) && m_gamemode != GameMode::ADVENTURE) {
		placeBlock(world);
		_nManager->sendBlockUpdatePacket(visibleBlocks.placeableBlock, selectedBlock);
	}

	//We get the visible blocks again to update them after a block has been pressed
	getVisibleBlocks(camera, world);
}


void Player::kbHandler(const Camera& camera, World* world, InputManager* _iManager, float deltaTime) {
	math::vec3 camForward = camera.getForward();
	math::vec3 forward = math::normalize(math::vec3(camForward.x, 0.0f, camForward.z));
	math::vec3 side = math::normalize(math::cross(camForward, math::vec3(0.0f, 1.0f, 0.0f)));

	if (_iManager->isKeyDown(sf::Keyboard::Z)) {
		m_velocity += forward * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::S)) {
		m_velocity -= forward * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::Q)) {
		m_velocity -= side * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::D)) {
		m_velocity += side * SPEED * deltaTime;
	}
	
	if (_iManager->isKeyDown(sf::Keyboard::Space)) {
		if (GameModeCanFly(m_gamemode))
			m_velocity.y += 0.375f*deltaTime;
		else if (m_canJump) 
			m_velocity.y = 0.12f;
	}

	if (GameModeCanFly(m_gamemode)) {
		if (_iManager->isKeyDown(sf::Keyboard::LShift)) {
			m_velocity.y -= 0.375f*deltaTime;
		}
	}

	// Gravity
	if (!GameModeCanFly(m_gamemode))
		m_velocity.y -=  GRAVITY * deltaTime;
	else {
		m_velocity.y *= 0.95;
	}
	m_velocity.x *= HORIZONTAL_DRAG;
	m_velocity.z *= HORIZONTAL_DRAG;
	m_velocity.y *= VERTICAL_DRAG;

	position += m_velocity;
}

math::vec3 Player::getEyePos() const {
	return math::vec3(position.x + 0.5f, position.y + 1.5f, position.z + 0.5f);
}

void Player::getVisibleBlocks(const Camera& camera, World* world) {
	math::ivec3 pos = vecToBlock(camera.getPosition());
	visibleBlocks.lookingAtBlock = false;
	visibleBlocks.isInsideBlock = world->getBlock(pos.x, pos.y, pos.z) ? true : false;

	math::vec3 rayPosition = camera.getPosition();
	for (unsigned int i = 0; i < PRECISION; i++) {
		rayPosition += camera.getForward() * m_reachDistance / (float)PRECISION;

		visibleBlocks.breakableBlock = vecToBlock(rayPosition);
		uint8_t blockID = world->getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);

		if (blockID) {
			visibleBlocks.lookingAtBlock = true;
			rayPosition -= camera.getForward() * m_reachDistance / (float)PRECISION;
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
	handler.placeParticlesAroundBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
}

math::ivec3 Player::vecToBlock(const math::vec3& vec) {
	return math::ivec3(math::floor(vec.x), math::floor(vec.y), math::floor(vec.z));
}

void Player::collideWithWorld(World* _world){
	math::ivec3 playerCenterBlock = vecToBlock(position);
	std::vector<AABB> blocksToCollideWith;
	m_canJump = false;

	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 3; y++){
			for(int z = -1; z < 2; z++){
				math::ivec3 iBlockPos = playerCenterBlock + math::ivec3(x, y, z);

				if(_world->getBlock(iBlockPos.x, iBlockPos.y, iBlockPos.z)){
					math::vec3 blockPos = math::vec3(iBlockPos.x, iBlockPos.y, iBlockPos.z);
					AABB blockBox(blockPos, math::vec3(1, 1, 1));
					blocksToCollideWith.push_back(blockBox);
				}
			}
		}
	}

	// Sort blocks
	std::stable_sort(blocksToCollideWith.begin(), blocksToCollideWith.end(), compareDistance);

	for(auto& i : blocksToCollideWith){
		AABB playerBox(position, math::vec3(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH));
		if(Utils::collideBoxes(playerBox, i) == Y_AXIS){
			if(i.position.y < position.y){
				m_canJump = true;
				m_velocity.y = 0.0f;
			}
		}

		position = playerBox.position;
	}
}

bool Player::compareDistance(AABB a, AABB b){
	math::vec3 centerPlayerPos = position + math::vec3(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2, PLAYER_WIDTH / 2);

	math::vec3 centerBlockPos1 = a.position + math::vec3(0.5, 0.5, 0.5);
	math::vec3 centerBlockPos2 = b.position + math::vec3(0.5, 0.5, 0.5);

	float distance1 = math::length(math::fabs(centerBlockPos1 - centerPlayerPos));
	float distance2 = math::length(math::fabs(centerBlockPos2 - centerPlayerPos));

	return distance1 < distance2;
}
