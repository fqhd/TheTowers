#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFontShader.hpp"
#include "GUIFont.hpp"
#include "GUIImage.hpp"
#include "GUICheckbox.hpp"
#include "GUISlider.hpp"
#include "GUIKeybox.hpp"

class GUIHandler {
public:

	void init();
	void update();
	void render();
	void destroy();

	std::vector<GUIButton> buttons;
	std::vector<GUIImage> images;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUISlider> sliders;
	std::vector<GUIKeybox> keyboxes;

	std::vector<GUITextMesh> textMeshes;
	std::vector<GUIFont> fonts;

private:

	void renderGUI();
	void renderFonts();

	GUIRenderer m_guiRenderer;
	GUIShader m_guiShader;
	GUIFontShader m_fontShader;

	glm::mat4 m_matrix;


};

#endif
