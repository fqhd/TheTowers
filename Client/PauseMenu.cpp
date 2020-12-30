#include "PauseMenu.hpp"
#include "Constants.hpp"

const float MENU_WIDTH = 900.0f;
const float MENU_HEIGHT = 600.0f;
const float MENU_BG_WIDTH = MENU_WIDTH + 2.0f;
const float MENU_BG_HEIGHT = MENU_HEIGHT + 2.0f;

void PauseMenu::init(GUIFont* font, Settings& settings){

     m_handler.init(font);

     if(settings.vsync)
          Window::setVerticalSyncEnabled(true);
     else
          Window::setVerticalSyncEnabled(false);

     m_handler.images.push_back(GUIImage(glm::vec4(0, 0, Constants::getScreenWidth(), Constants::getScreenHeight()), ColorRGBA8(0, 0, 0, 150)));
     m_handler.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_BG_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_BG_HEIGHT / 2.0f, MENU_BG_WIDTH, MENU_BG_HEIGHT), ColorRGBA8(50, 50, 50, 255)));
     m_handler.images.push_back(GUIImage(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2, Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f, MENU_WIDTH, MENU_HEIGHT), ColorRGBA8(20, 20, 20, 255)));
     m_handler.images.push_back(GUIImage(glm::vec4(600, 190, 128, 128), ColorRGBA8(0, 0, 0, 255)));

     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50,
          Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 450, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.showFPS));


     m_handler.checkboxes.push_back(GUICheckbox(glm::vec4(Constants::getScreenWidth() / 2 - MENU_WIDTH / 2 + 50,
          Constants::getScreenHeight() / 2.0f - MENU_HEIGHT / 2.0f + 400, 16, 16), ColorRGBA8(220, 50, 255, 255),
          ColorRGBA8(90, 90, 90, 255), settings.vsync));

     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 200), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 250), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(300, 300), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), 1.0f));
     m_handler.sliders.push_back(GUISlider(glm::vec2(500, 150), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.mouseSensibility / Constants::getMaxMouseSensibility()));
     m_handler.sliders.push_back(GUISlider(glm::vec2(500, 100), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.playerSpeed / Constants::getMaxPlayerSpeed()));
     m_handler.sliders.push_back(GUISlider(glm::vec2(800, 150), 250.0f, ColorRGBA8(156, 0, 252, 255), ColorRGBA8(255, 255, 255, 255), settings.renderDistance / Constants::getMaxRenderDistance()));


     m_handler.boxes.push_back(GUISelectbox(glm::vec4(850, 425, 200, 30), ColorRGBA8(255, 255, 255, 255), 3));

     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.front));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(220 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.back));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.left));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(420 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.right));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 620, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.up));
     m_handler.keyboxes.push_back(GUIKeybox(glm::vec4(620 + 100, 580, 32, 32), ColorRGBA8(255, 255, 255, 255), settings.down));


}

void PauseMenu::update(GameStates& state, Settings& settings, Player& player){
     if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
          Window::setMouseCursorGrabbed(true);
          state = GameStates::PLAY;

          settings.showFPS = m_handler.checkboxes[0].isChecked();
          settings.vsync = m_handler.checkboxes[1].isChecked();
          if(settings.vsync)
               Window::setVerticalSyncEnabled(true);
          else
               Window::setVerticalSyncEnabled(false);

          unsigned int blueValue = ((int)(m_handler.sliders[2].getValue() * 5)) * 36;
          unsigned int greenValue = ((int)(m_handler.sliders[1].getValue() * 5)) * 6;
          unsigned int redValue = (int)(m_handler.sliders[0].getValue() * 5);

          player.selectedBlock = blueValue + greenValue + redValue;

          settings.mouseSensibility = m_handler.sliders[3].getValue() * Constants::getMaxMouseSensibility();
          settings.playerSpeed = m_handler.sliders[4].getValue() * Constants::getMaxPlayerSpeed();

          settings.front = m_handler.keyboxes[0].getValue();
          settings.back = m_handler.keyboxes[1].getValue();
          settings.left = m_handler.keyboxes[2].getValue();
          settings.right = m_handler.keyboxes[3].getValue();
          settings.up = m_handler.keyboxes[4].getValue();
          settings.down = m_handler.keyboxes[5].getValue();
          settings.renderDistance = m_handler.sliders[5].getValue() * Constants::getMaxRenderDistance();

     }

     m_handler.images[3].color = ColorRGBA8(m_handler.sliders[0].getValue() * 255, m_handler.sliders[2].getValue() * 255, m_handler.sliders[2].getValue() * 255, 255);

     m_handler.update();

}

void PauseMenu::render(){

     m_handler.render();

     m_handler.renderFont("Show FPS", 280, 510, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Vertical Sync", 280, 460, 0.5f, ColorRGBA8(255, 255, 255, 255));


     m_handler.renderFont("R: " + std::to_string((int)(m_handler.sliders[0].getValue() * 255)), 220, 200, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("G: " + std::to_string((int)(m_handler.sliders[1].getValue() * 255)), 220, 250, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("B: " + std::to_string((int)(m_handler.sliders[2].getValue() * 255)), 220, 300, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Mouse Sensibility: " + std::to_string((int)(m_handler.sliders[3].getValue() * Constants::getMaxMouseSensibility())), 220, 150, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Player Speed: " + std::to_string((int)(m_handler.sliders[4].getValue() * Constants::getMaxPlayerSpeed())), 220, 100, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("Fullscreen", 870, 430, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("Borderless", 870, 460, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("Windowed", 870, 490, 0.5f, ColorRGBA8(0, 0, 0, 255));
     m_handler.renderFont("RenderDistance", 850, 110, 0.5f, ColorRGBA8(255, 255, 255, 255));

     m_handler.renderFont("Front: ", 220, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Back: ", 220, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Left: ", 420, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Right: ", 420, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Up: ", 620, 620, 0.5f, ColorRGBA8(255, 255, 255, 255));
     m_handler.renderFont("Down: ", 620, 580, 0.5f, ColorRGBA8(255, 255, 255, 255));

}

void PauseMenu::destroy(){
     m_handler.destroy();
}
