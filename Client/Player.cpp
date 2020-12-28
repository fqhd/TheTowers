#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

#include <iostream>


void Player::init(){
    camera.init(glm::vec3((WORLD_SIZE * CHUNK_WIDTH) / 2, CHUNK_WIDTH, (WORLD_SIZE * CHUNK_WIDTH) / 2));
}

void Player::update(Settings& settings, std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, sf::TcpSocket& socket){

     breakBlocks(colors, renderer, world, socket);
     placeBlocks(colors, renderer, world, socket);
     camera.update(settings, deltaTime);

}

void Player::breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

     //Breaking blocks
     if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < PRECISION; i++){
               rayPosition += camera.getForward() * (DISTANCE / (float)PRECISION);
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){

                    //Sending block update information to server
                    sf::Packet packet;
                    packet << (uint8_t)rayPosition.x << (uint8_t)rayPosition.y << (uint8_t)rayPosition.z << (uint8_t)0;
                    socket.send(packet);
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, 0);

                    //Adding particles
                    for(unsigned int j = 0; j < 100; j++){
                         renderer.particles.push_back(Particle(colors[blockID], glm::vec3((int)rayPosition.x, (int)rayPosition.y,
                         (int)rayPosition.z) + glm::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), glm::vec3((rand()%10) - 5, 10,
                         (rand()%10) - 5) * 0.20f, 1.25f, 1.0f, 0.0f, 0.125f));
                    }
                    break;
               }
          }
    }
}

void Player::placeBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

     //Placing blocks
    if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < PRECISION; i++){
               rayPosition += camera.getForward() * (DISTANCE / (float)PRECISION);
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){
                    rayPosition -= camera.getForward() * (DISTANCE / (float)PRECISION);

                    //Sending block update information to server
                    sf::Packet packet;
                    packet << (uint8_t)rayPosition.x << (uint8_t)rayPosition.y << (uint8_t)rayPosition.z << selectedBlock;
                    socket.send(packet);
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, selectedBlock);

                    break;
               }
          }
    }
}
