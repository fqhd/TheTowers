#ifndef GUI_CHECKBOX_H
#define GUI_CHECKBOX_H

#include "GUIRenderer.hpp"
#include "../Input/InputManager.hpp"


class GUICheckbox {
public:

	GUICheckbox(const glm::vec4& destRect, unsigned int _layer, bool checked = false);
	void update(InputManager* _manager, float deltaTime);
	void render(GUIRenderer& renderer);
	bool isChecked();

	unsigned int layer;

private:

	glm::vec4 m_originalRect;
	glm::vec4 m_targetRect;
	glm::vec4 m_shadowRect;
	glm::vec4 m_destRect;
	bool m_isChecked = false;

	ColorRGBA8 m_offColor;
	ColorRGBA8 m_onColor;
	ColorRGBA8 m_currentColor;

};

#endif
