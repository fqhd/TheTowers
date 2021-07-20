#include "Player.hpp"
#include "Engine/Utils/Utils.hpp"
#include <iostream>

const unsigned int PRECISION = 50;


void Player::init(unsigned int _reachDistance) {
	m_reachDistance = _reachDistance;
	position = math::vec3(0, 3, 0);
}

void Player::update(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager, float deltaTime) {
	mouseHandler(camera, handler, world, _nManager, _iManager);
	kbHandler(camera, world, _iManager, deltaTime);
	collideWithWorld(world);
}

void Player::mouseHandler(const Camera& camera, ParticleHandler& handler, World* world, NetworkManager* _nManager, InputManager* _iManager) {
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


void Player::kbHandler(const Camera& camera, World* world, InputManager* _iManager, float deltaTime) {
	math::vec3 camForward = camera.getForward();
	math::vec3 forward = math::normalize(math::vec3(camForward.x, 0.0f, camForward.z));
	math::vec3 side = math::normalize(math::cross(camForward, math::vec3(0.0f, 1.0f, 0.0f)));

	if (_iManager->isKeyDown(sf::Keyboard::Z)) {
		position += forward * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::S)) {
		position -= forward * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::Q)) {
		position -= side * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::D)) {
		position += side * SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::LShift)) {
		position.y -= SPEED * deltaTime;
	}

	if (_iManager->isKeyDown(sf::Keyboard::Space)) {
		position.y += SPEED * deltaTime;
	}
}

math::vec3 Player::getEyePos(){
	return math::vec3(position.x + 0.5f, position.y + 0.5f, position.z + 0.5f);
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
	// handler.placeParticlesAroundBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
}

math::ivec3 Player::vecToBlock(const math::vec3& vec) {
	return math::ivec3(math::floor(vec.x), math::floor(vec.y), math::floor(vec.z));
}

void Player::collideWithWorld(World* _world){
	math::ivec3 playerCenterBlock = vecToBlock(position);

	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			for(int z = -1; z < 2; z++){
				math::ivec3 iBlockPos = playerCenterBlock + math::ivec3(x, y, z);

				if(_world->getBlock(iBlockPos.x, iBlockPos.y, iBlockPos.z)){
					math::vec3 blockPos = math::vec3(iBlockPos.x, iBlockPos.y, iBlockPos.z);

					AABB playerBox(position, math::vec3(1, 1, 1));
					AABB blockBox(blockPos, math::vec3(1, 1, 1));
					Utils::collideBoxes(playerBox, blockBox);
					position = playerBox.position;
				}
			}
		}
	}
}