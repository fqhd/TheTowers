#ifndef TEXT_MESH_H
#define TEXT_MESH_H

#include <GL/glew.h>

struct GUITextVertex {
	glm::vec2 position;
	glm::vec2 uv;
};

class GUITextMesh {
public:

     void init();
     void render();
     void destroy();

	std::vector<GUITextVertex> vertices;

private:

     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;

};

#endif
