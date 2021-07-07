#include "GUIRect.hpp"

GUIRect::GUIRect(const glm::vec4& d, const ColorRGBA8& c){
	destRect = d;
	color = c;
}

void GUIRect::render(GUIRenderer& renderer){
	renderer.draw(destRect, color);
}
