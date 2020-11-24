#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Info.hpp"
#include <iostream>



void Player::init(){
    camera.init(glm::vec3((WORLD_SIZE * CHUNK_WIDTH) / 2, CHUNK_WIDTH, (WORLD_SIZE * CHUNK_WIDTH) / 2));
    position = glm::vec3((WORLD_SIZE * CHUNK_WIDTH) / 2, CHUNK_WIDTH, (WORLD_SIZE * CHUNK_WIDTH) / 2);
}

void Player::update(sf::Window& window, const Settings& settings, const std::vector<vec3>& colors,
     ParticleRenderer& renderer, InputManager& manager, World& world, float deltaTime, uint8_t blockID, sf::TcpSocket& socket){

	movement(deltaTime, settings, manager);
	calculateCameraVectors(window, settings.mouseSensibility/100.0f);
	breakBlocks(colors, renderer, manager, world, blockID, socket);

}

void Player::calculateCameraVectors(sf::Window& window, float sensibility){


     sf::Vector2i mousePos = sf::Mouse::getPosition(window);

     sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);

     sf::Vector2i newPos = sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

     camera.m_pitch -= (mousePos.y - newPos.y) * sensibility;
     camera.m_yaw += (mousePos.x - newPos.x) * sensibility;

     if(camera.m_pitch >= 90.0f){
          camera.m_pitch = 89.0f;
     }
     if(camera.m_pitch <= -90.0f){
          camera.m_pitch = -89.0f;
     }

     camera.m_forward.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
     camera.m_forward.y = sin(glm::radians(camera.m_pitch));
     camera.m_forward.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));

     camera.m_position = glm::vec3(position.x + PLAYER_WIDTH / 2.0f, position.y + PLAYER_HEIGHT - 0.25f, position.z + PLAYER_WIDTH / 2.0f);
     camera.update(window);



}

void Player::movement(float deltaTime, const Settings& settings, InputManager& manager){


     glm::vec3 forward = glm::normalize(glm::vec3(camera.m_forward.x, 0.0f, camera.m_forward.z));
     glm::vec3 side = glm::normalize(glm::cross(camera.m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));

     if(manager.isKeyDown(settings.front)){
          position += forward * (float)settings.playerSpeed * deltaTime;
     }

     if(manager.isKeyDown(settings.back)){
          position -= forward * (float)settings.playerSpeed * deltaTime;
     }

     if(manager.isKeyDown(settings.left)){
          position -= side * (float)settings.playerSpeed * deltaTime;
     }


     if(manager.isKeyDown(settings.right)){
          position += side * (float)settings.playerSpeed * deltaTime;
     }

     if(manager.isKeyDown(settings.down)){
          position.y -= (float)settings.playerSpeed * deltaTime;
     }

     if(manager.isKeyDown(settings.up)){
          position.y += (float)settings.playerSpeed * deltaTime;
     }

}

void Player::breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, uint8_t b, sf::TcpSocket& socket){

     //Breaking blocks
     if(manager.isKeyPressed(sf::Mouse::Left)){
          glm::vec3 rayPosition = camera.m_position;
          for(unsigned int i = 0; i < PRECISION; i++){
               rayPosition += camera.m_forward * (DISTANCE / (float)PRECISION);
               uint8_t blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){

                    //Getting m_position
                    glm::vec3 blockPosition = glm::vec3((int)rayPosition.x, (int)rayPosition.x, (int)rayPosition.z);
                    glm::vec3 cameraPosition = camera.m_position;

                    glm::vec3 toCameraVector = cameraPosition - blockPosition;

                    Face f = getFace(toCameraVector.x, toCameraVector.y, toCameraVector.z);
                    if(f == FACE_0){
                         std::cout << "destroyed" << std::endl;
                    }

                    sf::Packet packet;

                    packet << (uint8_t)rayPosition.x << (uint8_t)rayPosition.y << (uint8_t)rayPosition.z << (uint8_t)0;

                    std::cout << "X: " << (unsigned int)rayPosition.x << std::endl;
                    std::cout << "Y: " << (unsigned int)rayPosition.y << std::endl;
                    std::cout << "Z: " << (unsigned int)rayPosition.z << std::endl;
                    std::cout << "B: " << (unsigned int)b << std::endl;

                    socket.send(packet);
                    
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, 0);
                    for(unsigned int j = 0; j < 100; j++){
                         renderer.particles.push_back(Particle(colors[blockID], glm::vec3((int)rayPosition.x, (int)rayPosition.y,
                         (int)rayPosition.z) + glm::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), glm::vec3((rand()%10) - 5, 10,
                         (rand()%10) - 5) * 0.20f, 1.25f, 1.0f, 0.0f, 0.125f));
                    }
                    break;
               }
          }
    }

    //Placing blocks
    if(manager.isKeyPressed(sf::Mouse::Right)){
          glm::vec3 rayPosition = camera.m_position;
          for(unsigned int i = 0; i < PRECISION; i++){
               rayPosition += camera.m_forward * (DISTANCE / (float)PRECISION);
               if(world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z)){
                    rayPosition -= camera.m_forward * (DISTANCE / (float)PRECISION);

                    sf::Packet packet;

                    packet << (uint8_t)rayPosition.x << (uint8_t)rayPosition.y << (uint8_t)rayPosition.z << b;

                    std::cout << "X: " << (unsigned int)rayPosition.x << std::endl;
                    std::cout << "Y: " << (unsigned int)rayPosition.y << std::endl;
                    std::cout << "Z: " << (unsigned int)rayPosition.z << std::endl;
                    std::cout << "B: " << (unsigned int)b << std::endl;

                    socket.send(packet);

                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, b);

                    break;

               }
          }
    }

}

Face Player::getFace(float x, float y, float z){
     return (Face)((FACE_0 + (x > 0)) * (fabs(x) > fabs(y) && fabs(x) > fabs(z))
  + (FACE_2 + (y > 0)) * (fabs(y) > fabs(x) && fabs(y) > fabs(z))
  + (FACE_4 + (z > 0)) * (fabs(z) > fabs(x) && fabs(z) > fabs(y)));
}
