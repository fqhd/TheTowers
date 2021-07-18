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
	m_guiRenderer.init();
	m_guiAssets.init();
	m_inputManager.init(&m_window);
	m_networkManager.connectToServer(_ip, m_config);
	m_world.init(m_networkManager, m_config);
	m_game.init(&m_inputManager, &m_world, &m_networkManager, &m_player);
	m_game.syncGameWithSettings(&m_settings);
	m_pause.init(&m_inputManager, &m_settings, &m_game, &m_guiRenderer, &m_guiAssets);
}

void Program::createWindow(){
	sf::ContextSettings cSettings;
	cSettings.majorVersion = 3;
	cSettings.minorVersion = 3;
	cSettings.depthBits = 24;
	cSettings.antialiasingLevel = 4;
	cSettings.stencilBits = 8;
	cSettings.attributeFlags = sf::ContextSettings::Attribute::Core;

	m_window.create(sf::VideoMode(1920, 1080), "TheTowers", sf::Style::Fullscreen, cSettings);
	if(glewInit() != GLEW_OK){
		std::cout << "Failed to initialize glew" << std::endl;
		return;
	}

	m_window.setVerticalSyncEnabled(true);

	//Enabling transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enabling depth
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	//Enabling back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}

void Program::gameloop(){
	while(m_state != GameStates::EXIT){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(m_inputManager.processInput()) m_state = GameStates::EXIT;
		glViewport(0, 0, m_inputManager.getWindowSize().x, m_inputManager.getWindowSize().y);

		float deltaTime = m_clock.restart().asSeconds();

		m_guiRenderer.begin();
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
	m_guiAssets.destroy();
	m_guiRenderer.destroy();
	m_game.destroy();
	m_pause.destroy();
	m_window.close();
}
