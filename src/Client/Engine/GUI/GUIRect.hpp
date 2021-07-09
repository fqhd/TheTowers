#ifndef GUI_RECT_H
#define GUI_RECT_H

#include "../Utils/Vertex.hpp"
#include "GUIRenderer.hpp"
#include <glm/glm.hpp>

class GUIRect {
public:

	GUIRect(const glm::vec4& d, const ColorRGBA8& c, unsigned int _layer);
	void render(GUIRenderer& renderer);

	glm::vec4 destRect;
	ColorRGBA8 color;
	unsigned int layer;

};

#endif
