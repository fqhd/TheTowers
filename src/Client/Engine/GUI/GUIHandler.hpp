#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFontShader.hpp"
#include "GUIFont.hpp"
#include "GUIRect.hpp"
#include "GUICheckbox.hpp"
#include "../Input/InputManager.hpp"

class GUIHandler {
public:

	void init(GUIFont* m_font);
	void update(InputManager* _manager, float deltaTime);
	void render();
	void destroy();


	std::vector<GUIButton> buttons;
	std::vector<GUIRect> rects;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUITextMesh> textMeshes;

private:

	void renderGUI();
	void renderFonts();

	GUIFont* m_font;
	GUIRenderer m_guiRenderer;
	GUIShader m_guiShader;
	GUIFontShader m_fontShader;

	glm::mat4 m_matrix;


};

#endif
