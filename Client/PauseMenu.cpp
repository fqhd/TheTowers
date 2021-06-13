#include "PauseMenu.hpp"
#include "Constants.hpp"

const float MENU_WIDTH = 900.0f;
const float MENU_HEIGHT = 600.0f;
const float MENU_BG_WIDTH = MENU_WIDTH + 2.0f;
const float MENU_BG_HEIGHT = MENU_HEIGHT + 2.0f;

void PauseMenu::init(GUIFont* font){

	if(settings.vsync) {
		Window::setVerticalSyncEnabled(true);
	} else {
		Window::setVerticalSyncEnabled(false);
	}


	addImages(settings, workspace);
	addCheckboxes(settings, workspace);
	addSliders(settings, workspace);
	addKeyboxes(settings, workspace);
	addText(settings, workspace);


}

void PauseMenu::addText(Settings& settings, GUICanvas& workspace){
	m_handler.textMeshes.emplace_back("Show FPS", glm::vec2(280, 510), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Vertical Sync", glm::vec2(280, 460), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Show Debug Info", glm::vec2(280, 410), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("RED", glm::vec2(220, 200), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("GREEN", glm::vec2(220, 250), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("BLUE", glm::vec2(220, 300), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Mouse Sensitivity", glm::vec2(220, 150), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Player Speed", glm::vec2(220, 100), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Density", glm::vec2(870, 320), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Gradient", glm::vec2(870, 220), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Front", glm::vec2(220, 620), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Back", glm::vec2(220, 580), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Left", glm::vec2(420, 620), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Right", glm::vec2(420, 580), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Up", glm::vec2(620, 620), ColorRGBA8(), 0);
	m_handler.textMeshes.emplace_back("Down", glm::vec2(620, 580), ColorRGBA8(), 0); workspace.textMeshes.emplace_back("Save", glm::vec2(990, 75), ColorRGBA8(), 0);

}

void PauseMenu::addImages(Settings& settings, GUICanvas& workspace){
	//Images
	workspace.images.push_back(GUIImage(glm::vec4(0, 0, Constants::getScreenWidth(), Constants::getScreenHeight()), ColorRGBA8(0, 0, 0, 150)));
	workspace.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_BG_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
	workspace.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
	workspace.images.push_back(GUIImage(glm::vec4(598, 188, 132, 132), ColorRGBA8(0, 0, 0, 255)));
	workspace.images.push_back(GUIImage(glm::vec4(600, 190, 128, 128), ColorRGBA8(0, 0, 0, 255)));

}

void PauseMenu::addCheckboxes(Settings& settings, GUICanvas& workspace){
	//Checkboxes
	workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.showFPS));
	workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.vsync));
	workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 350, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.showDebugInfo));

}


void PauseMenu::update(GameStates& state, Settings& settings, Player& player, GUICanvas& workspace){
	if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
		Window::setMouseCursorGrabbed(true);
		state = GameStates::PLAY;
		updatePlayerBlock(player, workspace);
		applySettingsToWorkspace(settings, workspace);
	} else if (workspace.buttons.at(0).isPressed()){
		applyWorkspaceToSettings(workspace, settings);
		updatePlayerBlock(player, workspace);
		Window::setMouseCursorGrabbed(true);
		state = GameStates::PLAY;

		if(settings.vsync){
			Window::setVerticalSyncEnabled(true);
		} else {
			Window::setVerticalSyncEnabled(false);
		}

	}

	workspace.images[4].color = ColorRGBA8(workspace.sliders[0].getValue() * 255, workspace.sliders[1].getValue() * 255, workspace.sliders[2].getValue() * 255, 255);

	workspace.update();
	updateValues(settings, workspace);

}

void PauseMenu::updateValues(Settings& settings, GUICanvas& workspace){
	settings.mouseSensibility = workspace.sliders[3].getValue() * Constants::getMaxMouseSensibility();
	settings.playerSpeed = workspace.sliders[4].getValue() * Constants::getMaxPlayerSpeed();
	settings.density = workspace.sliders[5].getValue() * Constants::getMaxDensity();
	settings.gradient = workspace.sliders[6].getValue() * Constants::getMaxGradient();
}

void PauseMenu::updatePlayerBlock(Player& player, GUICanvas& workspace){
  unsigned int blueValue = ((int)(workspace.sliders[2].getValue() * 5)) * 36;
  unsigned int greenValue = ((int)(workspace.sliders[1].getValue() * 5)) * 6;
  unsigned int redValue = (int)(workspace.sliders[0].getValue() * 5);
  player.selectedBlock = blueValue + greenValue + redValue;
}

void PauseMenu::applySettingsToWorkspace(Settings& settings, GUICanvas& workspace){
	//Set keyboxes
	workspace.keyboxes[0].value = settings.front;
	workspace.keyboxes[1].value = settings.back;
	workspace.keyboxes[2].value = settings.left;
	workspace.keyboxes[3].value = settings.right;
	workspace.keyboxes[4].value = settings.up;
	workspace.keyboxes[5].value = settings.down;

	//Setting Checkboxes
	workspace.checkboxes[0].isChecked = settings.showFPS;
	workspace.checkboxes[1].isChecked = settings.vsync;
	workspace.checkboxes[2].isChecked = settings.showDebugInfo;
}

void PauseMenu::applyWorkspaceToSettings(GUICanvas& workspace, Settings& settings){
	//Applying keyboxes
	settings.front = workspace.keyboxes[0].value;
	settings.back = workspace.keyboxes[1].value;
	settings.left = workspace.keyboxes[2].value;
	settings.right = workspace.keyboxes[3].value;
	settings.up = workspace.keyboxes[4].value;
	settings.down = workspace.keyboxes[5].value;

	//Applying Checkboxes
	settings.showFPS = workspace.checkboxes[0].isChecked;
	settings.vsync = workspace.checkboxes[1].isChecked;
	settings.showDebugInfo = workspace.checkboxes[2].isChecked;

}
