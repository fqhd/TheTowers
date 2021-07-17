#pragma once

#include "../Utils/Vertex.hpp"
#include "GUIRenderer.hpp"

class GUIRect {
public:

	GUIRect(const math::vec4& d, const ColorRGBA8& c, unsigned int _layer);
	void render(GUIRenderer* renderer);

	math::vec4 destRect;
	ColorRGBA8 color;
	unsigned int layer;

};
