#ifndef TEXT_MESH_H
#define TEXT_MESH_H

#include <GL/glew.h>


class GUITextMesh {
public:

     void init();
     void render();
     void destroy();

private:

     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;

};

#endif
