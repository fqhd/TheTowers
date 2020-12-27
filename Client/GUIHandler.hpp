#pragma once
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFont.hpp"
#include "GUIFontShader.hpp"
#include "GUIFontRenderer.hpp"
#include "GUIImage.hpp"
#include "GUICheckbox.hpp"
#include "GUISlider.hpp"
#include "GUISelectbox.hpp"
#include "GUIKeybox.hpp"

class GUIHandler {
public:

	void init(GUIFont* font);
	void update();
	void renderFont(const std::string& text, float x, float y, float scale, const ColorRGBA8& color);
	void render();
	void destroy();

	std::vector<GUIButton> buttons;
	std::vector<GUIImage> images;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUISlider> sliders;
	std::vector<GUISelectbox> boxes;
	std::vector<GUIKeybox> keyboxes;


private:

	GUIFont* m_font;
	GUIFontShader m_fShader;
	GUIFontRenderer m_fRenderer;

	GUIRenderer m_renderer;
	GUIShader m_shader;

	glm::mat4 m_matrix;



};
