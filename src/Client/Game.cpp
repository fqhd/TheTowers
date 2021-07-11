#include "Game.hpp"
#include <cstring>
#include <iostream>
#include <glm/gtc/noise.hpp>


void Game::init(InputManager* _manager, sf::IpAddress& _ip, Config& _c, TextureArray* _textureArray, GUIFont* _font) {
	m_textureArray = _textureArray;
	m_networkManager.connectToServer(_ip, _c);
	m_world.init(m_networkManager, _c, _textureArray);
	m_cubeMap.init();
	m_particleHandler.init();
	m_camera.init(_manager);
	m_vignette.init();
	m_entityHandler.init();
	m_blockOutline.init();
	m_guiHandler.init(_font, _textureArray);
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
	m_camera.update(_deltaTime);
	_player.update(m_camera, m_particleHandler, m_world, m_networkManager, m_inputManager);
	m_particleHandler.update(_deltaTime);
	m_networkManager.sendPositionDataToServer(m_camera);
}

void Game::render(Player& _player) {
	sf::Clock tmp;
	tmp.restart();

	// Rendering gameplay
	m_world.render(m_camera);
	m_blockOutline.render(_player, m_camera);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	m_cubeMap.render(m_camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_camera.getViewMatrix())));

	// Rendering vignette
	m_vignette.render();

	// Rendering UI
	m_textureArray->bind();
	m_guiHandler.render();
	m_textureArray->unbind();

	if(m_msPerFramePrintClock.getElapsedTime().asSeconds() >= 1.0f){
		std::cout << "ms: " << tmp.getElapsedTime().asMilliseconds() << std::endl;
		m_msPerFramePrintClock.restart();
	}
}

void Game::destroy() {
	m_vignette.destroy();
	m_guiHandler.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_cubeMap.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}

void Game::addGUI(){
	m_guiHandler.rects.push_back(GUIRect(glm::vec4(638, 358, 4, 4), ColorRGBA8(20, 20, 20, 255), 0));
}

void Game::syncGameWithSettings(Settings* _settings){
	m_vignette.setToggle(_settings->isVignetteToggled);
}
