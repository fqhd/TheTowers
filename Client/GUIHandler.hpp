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
#include "GUICanvas.hpp"

class GUIHandler {
public:

	void init();
	void createWorkspaces(unsigned int numWorkspaces); // Number of workspaces to create
	void updateWorkspace(unsigned int numWorkspace); // Number of workspace to update
	void renderWorkspace(unsigned int numWorkspace); // Number of workspace to render
	void updateAll(); // Update all workspaces
	void renderAll(); // Render all workspaces
	void destroy();

	std::vector<GUICanvas> workspaces;

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
