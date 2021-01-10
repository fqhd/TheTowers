#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include "Entity.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"
#include "Settings.hpp"
#include "Model.hpp"
#include <vector>
#include <unordered_map>
#include <SFML/Network.hpp>


class EntityHandler {
public:

     void init();
     void update(sf::UdpSocket& socket, float deltaTime);
     void render(Settings& settings, Camera& camera);
     void destroy();


private:

     //Functions
     void addEntity(uint8_t id, const glm::vec3& position, float pitch, float yaw);

     //Objects
     ModelShader m_shader;
     Model m_model;

     //Data Structures
     std::unordered_map<uint8_t, Entity> m_entities;

};

#endif
