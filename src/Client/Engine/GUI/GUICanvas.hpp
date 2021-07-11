#pragma once

#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFontShader.hpp"
#include "GUIFont.hpp"
#include "GUIRect.hpp"
#include "GUICheckbox.hpp"
#include "GUIRenderer.hpp"
#include "../Utils/TextureArray.hpp"
#include "../Input/InputManager.hpp"


class GUICanvas {
public:

    GUICanvas(GUIRenderer* _renderer, GUIShader* _guiShader, GUIFont* _font, GUIFontShader* _fontShader, TextureArray* _textureArray);
    void update(InputManager* _manager, float _deltaTime);
	void render();

	std::vector<GUIButton> buttons;
	std::vector<GUIRect> rects;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUILabel> labels;

private:

    GUIRenderer* m_guiRenderer = nullptr;
    GUIShader* m_guiShader = nullptr;
    GUIFontShader* m_fontShader = nullptr;
    GUIFont* m_font = nullptr;
    TextureArray* m_textureArray = nullptr;

};
