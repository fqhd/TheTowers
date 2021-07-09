#include "GUIRect.hpp"

GUIRect::GUIRect(const glm::vec4& d, const ColorRGBA8& c, unsigned int _layer){
	layer = _layer;
	destRect = d;
	color = c;
}

void GUIRect::render(GUIRenderer& renderer){
	renderer.draw(destRect, color, layer);
}
