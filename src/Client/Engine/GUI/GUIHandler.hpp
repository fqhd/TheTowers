#pragma once

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFontShader.hpp"
#include "GUIFont.hpp"
#include "GUIRect.hpp"
#include "GUICheckbox.hpp"
#include "../Utils/TextureArray.hpp"
#include "../Input/InputManager.hpp"

class GUIHandler {
public:

	void init(GUIFont* _font, TextureArray* _textureArray);
	void update(InputManager* _manager, float deltaTime);
	void render();
	void destroy();


	std::vector<GUIButton> buttons;
	std::vector<GUIRect> rects;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUILabel> labels;

private:

	void renderGUI();
	void renderFonts();

	GUIFont* m_font;
	TextureArray* m_textureArray = nullptr;
	GUIRenderer m_guiRenderer;
	GUIShader m_guiShader;
	GUIFontShader m_fontShader;

	glm::mat4 m_matrix;


};


