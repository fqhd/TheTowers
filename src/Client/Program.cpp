#include "Program.hpp"
#include <iostream>

void Program::run(sf::IpAddress& ip){
	initSystems(ip);
	gameloop();
	cleanUp();
}

void Program::initSystems(sf::IpAddress& _ip){
	m_config.loadFromFile();
	m_settings.loadFromFile();
	createWindow();
	m_debugMenu.init(&m_game, m_config);
	m_textureHandler.init();
	m_guiRenderer.init(m_config.getWindowWidth(), m_config.getWindowHeight());
	m_inputManager.init(&m_window);
	m_networkManager.connectToServer(_ip, &m_config);
	m_game.init(&m_inputManager, &m_networkManager, &m_guiRenderer, &m_textureHandler, &m_config, &m_settings);
	m_pause.init(&m_inputManager, &m_settings, &m_config, &m_guiRenderer);
}

void Program::createWindow(){
	// A few opengl window context settings
	sf::ContextSettings cSettings;
	cSettings.majorVersion = 3;
	cSettings.minorVersion = 3;
	cSettings.depthBits = 24;
	cSettings.antialiasingLevel = 4;
	cSettings.stencilBits = 8;
	cSettings.attributeFlags = sf::ContextSettings::Attribute::Core;

	// Creating the widnow
	m_window.create(sf::VideoMode(m_config.getWindowWidth(), m_config.getWindowHeight()), "TheTowers", sf::Style::Titlebar | sf::Style::Close, cSettings);
	if(glewInit() != GLEW_OK){
		std::cout << "Failed to initialize glew" << std::endl;
		return;
	}

	//Enabling transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enabling depth
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	//Enabling back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Ready for game settings
	// m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(144);
	m_window.setMouseCursorGrabbed(true);
	m_window.setMouseCursorVisible(false);

	// Centering the window
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.setPosition(sf::Vector2i(desktop.width/2 - m_window.getSize().x/2, desktop.height/2 - m_window.getSize().y/2));
}

void Program::gameloop(){
	while(m_state != GameStates::EXIT){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_inputManager.getWindowSize().x, m_inputManager.getWindowSize().y);

		float deltaTime = m_clock.restart().asSeconds();

		m_guiRenderer.begin();
		if(m_settings.isDebugToggled) m_debugMenu.render(&m_guiRenderer);
		if(m_state == GameStates::PLAY){
			m_game.update(m_state, deltaTime);
			m_game.render();
			if(m_settings.isDebugToggled) m_debugMenu.render(&m_guiRenderer);
		}else if(m_state == GameStates::PAUSE){
			m_pause.update(m_state, deltaTime);
			m_game.render();
			if(m_settings.isDebugToggled) m_debugMenu.render(&m_guiRenderer);
			m_pause.render();
		}
		m_guiRenderer.end();
		m_guiRenderer.render();

		m_window.display();
	}
}

void Program::cleanUp(){
	m_textureHandler.destroy();
	m_guiRenderer.destroy();
	m_game.destroy();
	m_window.close();
}
