#include "Player.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include <iostream>


void Player::init(){
    camera.init(glm::vec3((WORLD_SIZE * CHUNK_WIDTH) / 2, CHUNK_WIDTH, (WORLD_SIZE * CHUNK_WIDTH) / 2));
    position = glm::vec3((WORLD_SIZE * CHUNK_WIDTH) / 2, CHUNK_WIDTH, (WORLD_SIZE * CHUNK_WIDTH) / 2);
}

void Player::update(sf::Window& window, const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world, float deltaTime){


	movement(deltaTime);
	calculateCameraVectors(window);
	breakBlocks(colors, renderer, manager, world);

}

void Player::calculateCameraVectors(sf::Window& window){


     sf::Vector2i mousePos = sf::Mouse::getPosition(window);

     sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);

     sf::Vector2i newPos = sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

     camera.m_pitch -= (mousePos.y - newPos.y) * 0.25f;
     camera.m_yaw += (mousePos.x - newPos.x) * 0.25f;

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

void Player::movement(float deltaTime){


     glm::vec3 forward = glm::normalize(glm::vec3(camera.m_forward.x, 0.0f, camera.m_forward.z));
     glm::vec3 side = glm::normalize(glm::cross(camera.m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
          position += forward * m_speed * deltaTime;
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
          position -= side * m_speed * deltaTime;
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          position -= forward * m_speed * deltaTime;
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          position += side * m_speed * deltaTime;
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
          position.y -= m_speed * deltaTime;
     }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
          position.y += m_speed * deltaTime;
     }

}

void Player::breakBlocks(const std::vector<vec3>& colors, ParticleRenderer& renderer, InputManager& manager, World& world){

     //Breaking blocks
     if(manager.isKeyPressed(sf::Mouse::Left)){
          glm::vec3 rayPosition = camera.m_position;
          for(unsigned int i = 0; i < PRECISION; i++){
               rayPosition += camera.m_forward * (DISTANCE / (float)PRECISION);
               char blockID = world.getBlock(rayPosition.x, rayPosition.y, rayPosition.z);
               if(blockID){
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, 0);
                    for(unsigned int j = 0; j < 100; j++){
                         renderer.particles.push_back(Particle(colors[blockID - 1], glm::vec3((int)rayPosition.x, (int)rayPosition.y,
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
                    world.setBlock(rayPosition.x, rayPosition.y, rayPosition.z, m_selectedBlock);
                    break;

               }
          }
    }

}
