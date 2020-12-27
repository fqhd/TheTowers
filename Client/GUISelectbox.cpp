#include "GUISelectbox.hpp"
#include <iostream>

GUISelectbox::GUISelectbox(const glm::vec4& quad, const ColorRGBA8& color, unsigned int numComponents){


     for(unsigned int i = 0; i < numComponents; i++){

          components.push_back(GUIComponent(glm::vec4(quad.x, quad.y + i*quad.w, quad.z, quad.w), color));

     }

}

void GUISelectbox::update(){

     for(auto& i : components){
          i.update(components);
     }

}

void GUISelectbox::render(GUIRenderer& renderer){
     for(auto& i : components){
          i.render(renderer);
     }
}
