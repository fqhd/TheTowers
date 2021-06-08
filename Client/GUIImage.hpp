#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H
#include "Vertex.hpp"
#include "GUIRenderer.hpp"
#include <glm/glm.hpp>

class GUIImage {
public:


	GUIImage(const glm::vec4& d, const ColorRGBA8& c);
	void render(GUIRenderer& renderer);

	glm::vec4 destRect;
	ColorRGBA8 color;

private:


};

#endif
