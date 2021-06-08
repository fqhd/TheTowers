#ifndef GUI_CHECKBOX_H
#define GUI_CHECKBOX_H

#include "GUIRenderer.hpp"
#include "InputManager.hpp"


class GUICheckbox {
public:

	GUICheckbox(const glm::vec4& destRect, const ColorRGBA8& onColor, const ColorRGBA8& offColor, bool checked = false);
	void update();
	void render(GUIRenderer& renderer);

	bool isChecked = false;

private:

	glm::vec4 m_destRect;
	ColorRGBA8 m_offColor;
	ColorRGBA8 m_onColor;
	ColorRGBA8 m_currentColor;

};

#endif
