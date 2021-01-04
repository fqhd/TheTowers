#ifndef GUI_H
#define GUI_H

#include <glm/glm.hpp>

class GUI {
protected:

     void updateDestRect();

     glm::vec4 m_destRect;
     glm::vec4 m_ratio;

};

#endif
