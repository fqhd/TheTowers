#ifndef GUI_CANVAS_H
#define GUI_CANVAS_H

#include "GUIButton.hpp"
#include "GUIImage.hpp"
#include "GUICheckbox.hpp"
#include "GUISlider.hpp"
#include "GUIKeybox.hpp"
#include "GUITextMesh.hpp"
#include "GUIFontShader.hpp"
#include "GUIFont.hpp"
#include "GUIRenderer.hpp"
#include "GUIShader.hpp"
#include <glm/glm.hpp>


class GUICanvas {
public:

	void update();
	void render(GUIRenderer& guiRenderer, GUIShader& guiShader, GUIFontShader& fontShader, std::vector<GUIFont>& fonts, const glm::mat4& matrix);

	std::vector<GUIButton> buttons;
	std::vector<GUIImage> images;
	std::vector<GUICheckbox> checkboxes;
	std::vector<GUISlider> sliders;
	std::vector<GUIKeybox> keyboxes;
	std::vector<GUITextMesh> textMeshes;

private:

	// functions
	void renderFonts(GUIFontShader& fontShader, std::vector<GUIFont>& fonts, const glm::mat4& matrix);
	void renderGUI(GUIRenderer& guirenderer, GUIShader& guiShader, const glm::mat4& matrix);


};

#endif
