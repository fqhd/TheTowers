#include "PauseMenu.hpp"
#include "Constants.hpp"

const float MENU_WIDTH = 900.0f;
const float MENU_HEIGHT = 600.0f;
const float MENU_BG_WIDTH = MENU_WIDTH + 2.0f;
const float MENU_BG_HEIGHT = MENU_HEIGHT + 2.0f;

void PauseMenu::init(Settings& settings, GUICanvas& workspace){

     if(settings.vsync)
          Window::setVerticalSyncEnabled(true);
     else
          Window::setVerticalSyncEnabled(false);


	addImages(settings, workspace);
	addCheckboxes(settings, workspace);
	addSliders(settings, workspace);
	addKeyboxes(settings, workspace);
	addText(workspace);


}

void PauseMenu::addText(GUICanvas& workspace){
	workspace.textMeshes.emplace_back("Show FPS", glm::vec2(280, 510), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Vertical Sync", glm::vec2(280, 460), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Show Debug Info", glm::vec2(280, 410), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("RED", glm::vec2(220, 200), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("GREEN", glm::vec2(220, 250), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("BLUE", glm::vec2(220, 300), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Mouse Sensitivity", glm::vec2(220, 150), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Player Speed", glm::vec2(220, 100), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Density", glm::vec2(870, 320), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Gradient", glm::vec2(870, 220), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Front", glm::vec2(220, 620), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Back", glm::vec2(220, 580), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Left", glm::vec2(420, 620), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Right", glm::vec2(420, 580), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Up", glm::vec2(620, 620), ColorRGBA8(), 0);
	workspace.textMeshes.emplace_back("Down", glm::vec2(620, 580), ColorRGBA8(), 0);

}

void PauseMenu::addImages(Settings& settings, GUICanvas& workspace){
     //Images
     workspace.images.push_back(GUIImage(glm::vec4(0, 0, Constants::getScreenWidth(), Constants::getScreenHeight()), ColorRGBA8(0, 0, 0, 150)));
     workspace.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_BG_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     workspace.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
     workspace.images.push_back(GUIImage(glm::vec4(600, 190, 128, 128), ColorRGBA8(0, 0, 0, 255)));

}

void PauseMenu::addCheckboxes(Settings& settings, GUICanvas& workspace){
	//Checkboxes
     workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.showFPS));
     workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.vsync));
	workspace.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 350, 16, 16), ColorRGBA8(220, 50, 255, 255), ColorRGBA8(90, 90, 90, 255), settings.showDebugInfo));

}

void PauseMenu::addSliders(Settings& settings, GUICanvas& workspace){
	//Sliders
     workspace.sliders.push_back(GUISlider(glm::vec2(300, 200), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     workspace.sliders.push_back(GUISlider(glm::vec2(300, 250), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     workspace.sliders.push_back(GUISlider(glm::vec2(300, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     workspace.sliders.push_back(GUISlider(glm::vec2(500, 150), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.mouseSensibility / Constants::getMaxMouseSensibility()));
     workspace.sliders.push_back(GUISlider(glm::vec2(500, 100), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.playerSpeed / Constants::getMaxPlayerSpeed()));
     workspace.sliders.push_back(GUISlider(glm::vec2(800, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.density / Constants::getMaxDensity()));
     workspace.sliders.push_back(GUISlider(glm::vec2(800, 200), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.gradient / Constants::getMaxGradient()));
}

void PauseMenu::addKeyboxes(Settings& settings, GUICanvas& workspace){
	//Keyboxes
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.front));
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.back));
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.left));
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.right));
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.up));
     workspace.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.down));
}


void PauseMenu::update(GameStates& state, Settings& settings, Player& player, GUICanvas& workspace){
     if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
          Window::setMouseCursorGrabbed(true);
          state = GameStates::PLAY;

          settings.showFPS = workspace.checkboxes[0].isChecked();
          settings.vsync = workspace.checkboxes[1].isChecked();
		settings.showDebugInfo = workspace.checkboxes[2].isChecked();
          if(settings.vsync){
               Window::setVerticalSyncEnabled(true);
          } else {
               Window::setVerticalSyncEnabled(false);
          }

          unsigned int blueValue = ((int)(workspace.sliders[2].getValue() * 5)) * 36;
          unsigned int greenValue = ((int)(workspace.sliders[1].getValue() * 5)) * 6;
          unsigned int redValue = (int)(workspace.sliders[0].getValue() * 5);

          player.selectedBlock = blueValue + greenValue + redValue;

          settings.front = workspace.keyboxes[0].getValue();
          settings.back = workspace.keyboxes[1].getValue();
          settings.left = workspace.keyboxes[2].getValue();
          settings.right = workspace.keyboxes[3].getValue();
          settings.up = workspace.keyboxes[4].getValue();
          settings.down = workspace.keyboxes[5].getValue();

     }

     workspace.images[3].color = ColorRGBA8(workspace.sliders[0].getValue() * 255, workspace.sliders[1].getValue() * 255, workspace.sliders[2].getValue() * 255, 255);

     workspace.update();
     updateValues(settings, workspace);

}

void PauseMenu::updateValues(Settings& settings, GUICanvas& workspace){
     settings.mouseSensibility = workspace.sliders[3].getValue() * Constants::getMaxMouseSensibility();
     settings.playerSpeed = workspace.sliders[4].getValue() * Constants::getMaxPlayerSpeed();
     settings.density = workspace.sliders[5].getValue() * Constants::getMaxDensity();
     settings.gradient = workspace.sliders[6].getValue() * Constants::getMaxGradient();
}
