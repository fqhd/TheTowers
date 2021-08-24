#include "StartMenu.hpp"

void StartMenu::init(InputManager *inputManager,
                     Window *window,
                     GUIRenderer *guiRenderer,
                     Config *config,
                     Timer *deltaTimer) {
    m_gameShouldStart = false;
    m_inputManager = inputManager;
    m_window = window;
    m_guiRenderer = guiRenderer;
    m_config = config;
    m_deltaTimer = deltaTimer;
	
	int input_w = 200;
	int input_h = 50;
	int input_x = (int)(m_config->getWindowWidth() / 2 - input_w / 2);
	int input_y = (int)(m_config->getWindowHeight() / 2 - input_h / 2);
    m_ipinput.init(math::vec4(input_x, input_y, input_w, input_h));
}

void StartMenu::loop() {
    
    while (!m_gameShouldStart) {
        m_deltaTimer->restart();
	
		m_window->clear();
		if(m_inputManager->processInput()) return;
        if(m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) m_gameShouldStart = true;
		glViewport(0, 0, m_config->getWindowWidth(), m_config->getWindowHeight());

		//float deltaTime = m_deltaTimer->getElapsedTime();
		m_deltaTimer->restart();

		m_guiRenderer->begin();

        renderGUI();

		m_guiRenderer->end();
		m_guiRenderer->render();

		m_window->update();
        updateGUI();
	
    }
    
}

void StartMenu::renderGUI() {
    m_ipinput.render(m_guiRenderer);
}

void StartMenu::updateGUI() {
    m_ipinput.update(m_inputManager);
}