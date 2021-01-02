#include "EntityHandler.hpp"
#include "Utils.hpp"


void EntityHandler::init(){
     //Connecting to server?
     m_shader.init();
     m_model.loadFromFile("res/models/suzane.obj");

}

void EntityHandler::update(){
     for(auto& i : entities){
          //Code for updating position of entities based on received socket or whatever
     }
}

void EntityHandler::render(Settings& settings, Camera& camera){

     m_shader.bind();

     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadDensity(settings.density);
     m_shader.loadGradient(settings.gradient);

     for(auto& i : entities){
          m_shader.loadModelMatrix(i.transform.getMatrix());
          m_shader.loadColor(i.getColor());

          m_model.render();

     }

     m_shader.unbind();

}

void EntityHandler::destroy(){
     m_model.destroy();
     m_shader.destroy();
}
