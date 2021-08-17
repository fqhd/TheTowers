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
    m_input.init(math::vec4(100, 100, 200,  50));
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
    m_input.render(m_guiRenderer);
}

void StartMenu::updateGUI() {
    m_input.update(m_inputManager);
}