#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../Utils/Vertex.hpp"

struct GUITextVertex {
	GUITextVertex(const glm::vec2& p, const glm::vec2& u){
		position = p;
		uv = u;
	}
	glm::vec2 position;
	glm::vec2 uv;
};

class GUILabel {
public:

	GUILabel(const std::string& string, const glm::vec2& p, const ColorRGBA8& c);
	void render();
	void destroy();
	void pushData(const std::vector<GUITextVertex>& vertices);

	void setString(const std::string& string);

	ColorRGBA8 color;
	glm::vec2 position;
	bool needsMeshUpdate = true;
	const std::string& getString();

private:

	std::string m_string;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};

#endif
