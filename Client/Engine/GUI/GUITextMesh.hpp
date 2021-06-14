#ifndef TEXT_MESH_H
#define TEXT_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <Engine/Utils/Vertex.hpp>

struct GUITextVertex {
	GUITextVertex(const glm::vec2& p, const glm::vec2& u){
		position = p;
		uv = u;
	}
	glm::vec2 position;
	glm::vec2 uv;
};

class GUITextMesh {
public:

	GUITextMesh(const std::string& string, const glm::vec2& p, const ColorRGBA8& c, unsigned int fontIndex, bool visible = true);
	void render();
	void destroy();
	void pushData(const std::vector<GUITextVertex>& vertices);

	unsigned int getFontIndex();
	void setString(const std::string& string);

	ColorRGBA8 color;
	bool isVisible = true;
	glm::vec2 position;
	bool needsMeshUpdate = true;
	const std::string& getString();

private:

	unsigned int m_fontIndex = 0;
	std::string m_string;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

#endif
