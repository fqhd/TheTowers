#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "../Utils/Vertex.hpp"
#include "../Math/Math.hpp"

class GUILabel {
public:

	GUILabel();
	GUILabel(const std::string& string, const math::vec2& p, const ColorRGBA8& c);
	void init(const std::string& string, const math::vec2& p, const ColorRGBA8& c);
	void render();
	void destroy();
	void pushData(const std::vector<GUITextVertex>& vertices);
	void setString(const std::string& string);

	ColorRGBA8 color;
	math::vec2 position;
	bool needsMeshUpdate = true;
	const std::string& getString();

private:

	std::string m_string;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_numVertices = 0;

};
