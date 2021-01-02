#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include <iostream>


void Player::update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, sf::TcpSocket& socket){

     breakBlocks(camera, colors, renderer, world, socket);
     placeBlocks(camera, colors, renderer, world, socket);

}

void Player::breakBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

     if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < Constants::getPrecision(); i++){
               rayPosition += camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){

                    //Sending block update information to server
                    sf::Packet packet;
                    packet << (int)rayPosition.x << (int)rayPosition.y << (int)rayPosition.z << (uint8_t)0;
                    socket.send(packet);
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, 0);

                    renderer.placeParticlesAroundBlock((int)rayPosition.x, (int)rayPosition.y, (int)rayPosition.z, colors[blockID]);

                    break;
               }
          }
    }
}

void Player::placeBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

    if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < Constants::getPrecision(); i++){
               rayPosition += camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){
                    rayPosition -= camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());

                    //Sending block update information to server
                    sf::Packet packet;
                    packet << (int)rayPosition.x << (int)rayPosition.y << (int)rayPosition.z << (uint8_t)selectedBlock;
                    socket.send(packet);
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, selectedBlock);

                    break;
               }
          }
    }
}
