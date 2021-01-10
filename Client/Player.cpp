#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include <iostream>


void Player::update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleHandler& handler, World& world, float deltaTime, sf::TcpSocket& socket){

     getVisibleBlocks(camera, world);

     if(!visibleBlocks.lookingAtBlock) return;

     if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
          breakBlock(handler, colors, world);
          sendBlockData(visibleBlocks.breakableBlock, 0, socket);
     } else if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)){
          placeBlock(world);
          sendBlockData(visibleBlocks.placeableBlock, selectedBlock, socket);
     }

}

void Player::getVisibleBlocks(Camera& camera, World& world){
     visibleBlocks.lookingAtBlock = false;

     glm::vec3 rayPosition = camera.getPosition();
     for(unsigned int i = 0; i < Constants::getPrecision(); i++){
          rayPosition += camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
          uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
          if(blockID){

               visibleBlocks.lookingAtBlock = true;
               visibleBlocks.breakableBlock = vecToBlock(rayPosition);
               rayPosition -= camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
               visibleBlocks.placeableBlock = vecToBlock(rayPosition);
               break;
          }
     }
}

void Player::placeBlock(World& world){
     world.setBlock(visibleBlocks.placeableBlock.x, visibleBlocks.placeableBlock.y, visibleBlocks.placeableBlock.z, selectedBlock);
}

void Player::breakBlock(ParticleHandler& handler, std::vector<vec3>& colors, World& world){
     uint8_t blockID = world.getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
     world.setBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z, 0);
     handler.placeParticlesAroundBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z, colors[blockID]);
}

void Player::sendBlockData(const glm::uvec3& blockUpdate, uint8_t block, sf::TcpSocket& socket){

     sf::Packet packet;
     packet << (uint8_t)0 << (uint32_t)blockUpdate.x << (uint32_t)blockUpdate.y << (uint32_t)blockUpdate.z << block;
     socket.send(packet);

}

glm::uvec3 Player::vecToBlock(const glm::vec3& vec){
	return glm::uvec3(
     vec.x < 0 ? (unsigned int)vec.x - 1  : (unsigned int)vec.x,
     vec.y < 0 ? (unsigned int)vec.y - 1  : (unsigned int)vec.y,
     vec.z < 0 ? (unsigned int)vec.z - 1  : (unsigned int)vec.z);
}
