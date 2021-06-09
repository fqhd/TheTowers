#ifndef GUI_KEYBOX_H
#define GUI_KEYBOX_H
#include "../Utils/Vertex.hpp"
#include "GUIRenderer.hpp"

class GUIKeybox {
public:

	GUIKeybox(const glm::vec4& destRect, const ColorRGBA8& color, unsigned int v = 0);
	void update(std::vector<GUIKeybox>& keyboxes);
	void render(GUIRenderer& renderer);

	unsigned int value = 0;

private:

	glm::vec4 m_destRect;
	ColorRGBA8 m_baseColor;
	ColorRGBA8 m_currentColor;
	bool m_isSelected = false;


};

#endif
