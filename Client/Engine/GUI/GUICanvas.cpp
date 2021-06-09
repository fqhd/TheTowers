#include "GUICanvas.hpp"

void GUICanvas::update() {

	for (auto & i: buttons) {
		i.update();
	}

	for (auto & i: checkboxes) {
		i.update();
	}

	for (auto & i: sliders) {
		i.update();
	}

	for (auto & i: keyboxes) {
		i.update(keyboxes);
	}

}

void GUICanvas::render(GUIRenderer & guiRenderer, GUIShader & guiShader, GUIFontShader & fontShader, std::vector < GUIFont > & fonts,
	const glm::mat4 & matrix) {
	renderGUI(guiRenderer, guiShader, matrix);
	renderFonts(fontShader, fonts, matrix);
}

void GUICanvas::renderGUI(GUIRenderer & guiRenderer, GUIShader & guiShader,
	const glm::mat4 & matrix) {
	//Preaparing renderer for drawing
	guiRenderer.begin();

	//Batching images
	for (auto & i: images) {
		i.render(guiRenderer);
	}

	//Batching Buttons
	for (auto & i: buttons) {
		i.render(guiRenderer);
	}

	//Batching checkboxes
	for (auto & i: checkboxes) {
		i.render(guiRenderer);
	}

	for (auto & i: sliders) {
		i.render(guiRenderer);
	}

	for (auto & i: keyboxes) {
		i.render(guiRenderer);
	}


	guiRenderer.end();

	guiShader.bind();
	guiShader.loadMatrix(matrix);

	guiRenderer.render();

	guiShader.unbind();

}

void GUICanvas::renderFonts(GUIFontShader & fontShader, std::vector < GUIFont > & fonts,
	const glm::mat4 & matrix) {
	fontShader.bind();
	fontShader.loadMatrix(matrix);

	//Render all meshes, if a mesh needs an update, it gets passed to the updateMesh() function of the
	//GUIFont class where it will be updated based on its string of text

	for (auto & i: textMeshes) {
		if (!i.shouldBeDrawn) continue;
		if (i.needsUpdate) fonts.at(i.getFontIndex()).updateMesh(i);
		fontShader.loadColor(i.color);
		fontShader.loadPosition(i.position);
		fonts.at(i.getFontIndex()).bindTexture();
		i.render();
		fonts.at(i.getFontIndex()).unbindTexture();
	}

	fontShader.unbind();
}