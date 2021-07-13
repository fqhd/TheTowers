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

    GUIRenderer* guiRenderer = nullptr;
    GUIShader* guiShader = nullptr;

	std::vector<GUIButton> buttons;
	std::vector<GUIRect> rects;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUILabel> labels;

private:


    GUIFontShader* m_fontShader = nullptr;
    GUIFont* m_font = nullptr;
    TextureArray* m_textureArray = nullptr;

};
