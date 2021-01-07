#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include "Entity.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"
#include "Settings.hpp"
#include "Model.hpp"
#include <vector>
#include <SFML/Network.hpp>


class EntityHandler {
public:

     void init();
     void update(sf::UdpSocket& socket);
     void render(Settings& settings, Camera& camera);
     void destroy();

     std::vector<Entity> entities;

private:

     ModelShader m_shader;
     Model m_model;

};

#endif
