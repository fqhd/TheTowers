#ifndef QUAD_H
#define QUAD_H

class Quad {
public:

     void init();
     void render();
     void destroy();

private:

     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_numVertices = 0;

};

#endif
