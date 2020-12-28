#ifndef GUI_SELECTBOX_H
#define GUI_SELECTBOX_H
#include "GUIComponent.hpp"


class GUISelectbox {
public:

     GUISelectbox(const glm::vec4& quad, const ColorRGBA8& color, unsigned int numComponents);
     void update();
     void render(GUIRenderer& renderer);

     std::vector<GUIComponent> components;


private:


};

#endif
