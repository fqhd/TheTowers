#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>

#include "Vertex.hpp"


class Model {
public:

     void loadFromFile(const std::string& model);
     void render();
     void destroy();

     GLuint getVaoID();
     GLuint getVboID();
     GLuint getEboID();
     GLuint getNumVertices();


private:


     GLuint m_numVertices = 0;
     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_eboID = 0;

};

#endif
