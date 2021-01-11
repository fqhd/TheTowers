#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "GUIButton.hpp"
#include "GUIShader.hpp"
#include "GUIFontShader.hpp"
#include "GUIFontRenderer.hpp"
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


private:

	GUIRenderer m_renderer;
	GUIShader m_shader;

	glm::mat4 m_matrix;


};

#endif
