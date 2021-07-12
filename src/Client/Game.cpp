#include "Game.hpp"
#include <cstring>
#include <iostream>
#include <glm/gtc/noise.hpp>


void Game::init(InputManager* _manager, sf::IpAddress& _ip, Config& _c, GUICanvas* _canvas, TextureArray* _textureArray) {
	m_canvas = _canvas;
	m_networkManager.connectToServer(_ip, _c);
	m_world.init(m_networkManager, _c, _textureArray);
	m_cubeMap.init();
	m_particleHandler.init();
	camera.init(_manager);
	m_vignette.init();
	m_entityHandler.init();
	m_blockOutline.init();
	addGUI();
	m_inputManager = _manager;
}

void Game::update(GameStates& _state, Player& _player, float _deltaTime) {
	// Switch state if key has been pressed
	if (m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) {
		m_inputManager->setMouseGrabbed(false);
		_state = GameStates::PAUSE;
	}

	m_entityHandler.update(m_networkManager, _deltaTime);
	m_networkManager.receiveGameUpdatePacket(m_world, m_particleHandler, m_entityHandler);
	camera.update(_deltaTime);
	_player.update(camera, m_particleHandler, m_world, m_networkManager, m_inputManager);
	m_particleHandler.update(_deltaTime);
	m_networkManager.sendPositionDataToServer(camera);
}

void Game::render(Player& _player) {
	sf::Clock tmp;
	tmp.restart();

	// Rendering gameplay
	m_world.render(camera);
	m_blockOutline.render(_player, camera);
	m_particleHandler.render(camera);
	m_entityHandler.render(camera);
	m_cubeMap.render(camera.getProjectionMatrix(), camera.getViewMatrix());

	// Rendering vignette
	m_vignette.render();

	// Rendering UI
	m_canvas->render();

	if(m_msPerFramePrintClock.getElapsedTime().asSeconds() >= 1.0f){
		std::cout << "ms: " << tmp.getElapsedTime().asSeconds() * 1000.0f << std::endl;
		m_msPerFramePrintClock.restart();
	}
}

void Game::destroy() {
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_cubeMap.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}

void Game::addGUI(){
	m_canvas->rects.push_back(GUIRect(glm::vec4(638, 358, 4, 4), ColorRGBA8(20, 20, 20, 255), 0));
}

void Game::syncGameWithSettings(Settings* _settings){
	m_vignette.setToggle(_settings->isVignetteToggled);
}
