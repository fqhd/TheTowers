#include "EntityHandler.hpp"
#include "Utils.hpp"


void EntityHandler::init(){
     //Connecting to server?
     m_shader.init();
     m_model.loadFromFile("res/models/suzane.obj");

}

void EntityHandler::update(sf::UdpSocket& socket, float deltaTime){
     sf::Packet packet;
     sf::IpAddress remoteIp;
     unsigned short remotePort;


     while(socket.receive(packet, remoteIp, remotePort) == sf::Socket::Done){
          glm::vec3 position;
          float pitch, yaw;
          uint8_t remoteID;

          packet >> remoteID >> position.x >> position.y >> position.z >> pitch >> yaw;

          if(m_entities.find(remoteID) != m_entities.end()){
               m_entities[remoteID].setTargetPosition(position);
               m_entities[remoteID].setForward(pitch, yaw);
          }else{
               addEntity(remoteID, position, pitch, yaw);
          }
     }

     //Update Entities
     for(auto it = m_entities.begin(); it != m_entities.end(); it++){
          it->second.update(deltaTime);
     }

}

void EntityHandler::addEntity(uint8_t id, const glm::vec3& position, float pitch, float yaw){
     Entity entity(Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
     entity.setTargetPosition(position);
     entity.setForward(pitch, yaw);
     m_entities[id] = entity;
}

void EntityHandler::removeEntity(uint8_t id){
     m_entities.erase(id);
}

void EntityHandler::render(Settings& settings, Camera& camera, const std::vector<vec3>& colors){

     m_shader.bind();

     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadDensity(settings.density);
     m_shader.loadGradient(settings.gradient);

     for(auto it = m_entities.begin(); it != m_entities.end(); it++){
          m_shader.loadModelMatrix(it->second.transform.getMatrix());
		m_shader.loadColor(colors[it->first]);

          m_model.render();

     }

     m_shader.unbind();

}

void EntityHandler::destroy(){
     m_model.destroy();
     m_shader.destroy();
}
