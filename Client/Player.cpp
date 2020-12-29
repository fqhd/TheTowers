#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"


void Player::update(Camera& camera, Settings& settings, std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, float deltaTime, sf::TcpSocket& socket){

     breakBlocks(camera, colors, renderer, world, socket);
     placeBlocks(camera, colors, renderer, world, socket);

}

void Player::breakBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

     //Breaking blocks
     if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < Constants::getPrecision(); i++){
               rayPosition += camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){

                    //Sending block update information to server
                    sf::Packet packet;
                    packet << (uint8_t)rayPosition.x << (uint8_t)rayPosition.y << (uint8_t)rayPosition.z << (uint8_t)0;
                    socket.send(packet);
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, 0);

                    //Adding particles
                    for(unsigned int j = 0; j < 100; j++){
                         renderer.particles.emplace_back(colors[blockID], glm::vec3((int)rayPosition.x, (int)rayPosition.y,
                         (int)rayPosition.z) + glm::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), glm::vec3((rand()%10) - 5, 10,
                         (rand()%10) - 5) * 0.20f, 1.25f, 0.0f, 0.125f);
                    }
                    break;
               }
          }
    }
}

void Player::placeBlocks(Camera& camera, const std::vector<vec3>& colors, ParticleRenderer& renderer, World& world, sf::TcpSocket& socket){

     //Placing blocks
    if(InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)){
          glm::vec3 rayPosition = camera.getPosition();
          for(unsigned int i = 0; i < Constants::getPrecision(); i++){
               rayPosition += camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){
                    rayPosition -= camera.getForward() * (Constants::getPlayerReachDistance() / (float)Constants::getPrecision());

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
