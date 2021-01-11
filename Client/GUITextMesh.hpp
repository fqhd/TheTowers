#ifndef TEXT_MESH_H
#define TEXT_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Vertex.hpp"


struct GUITextVertex {
	glm::vec2 position;
	glm::vec2 uv;
};

class GUITextMesh {
public:

     GUITextMesh(const std::string& string, const ColorRGBA8& c, unsigned int fontIndex);
     void render();
     void destroy();
	void pushData(const std::vector<GUITextVertex>& vertices);

	unsigned int getFontIndex();
	void setString(const std::string& string);

	ColorRGBA8 color;
	bool needsUpdate = true;

private:

	unsigned int m_fontIndex = 0;
	std::string m_string;
     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
	GLuint m_numVertices;

};

#endif
