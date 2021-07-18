#include "Game.hpp"
#include <cstring>
#include <iostream>


void Game::init(InputManager* _iManager, World* _world, NetworkManager* _nManager, Player* _player) {
	m_networkManager = _nManager;
	m_inputManager = _iManager;
	m_player = _player;
	m_world  = _world;

	m_cubeMap.init();
	m_particleHandler.init();
	camera.init(_iManager);
	m_vignette.init();
	m_entityHandler.init();
	m_blockOutline.init();
	m_hud.init();
	m_player->init();
}

void Game::update(GameStates& _state, float _deltaTime) {
	// Switch state if key has been pressed
	if (m_inputManager->isKeyPressed(sf::Keyboard::Escape) || !m_inputManager->hasFocus()) {
		m_inputManager->setMouseGrabbed(false);
		m_inputManager->setMouseVisible(true);
		_state = GameStates::PAUSE;
	}
	frameCounter.tick(_deltaTime);
	m_entityHandler.update(m_networkManager, _deltaTime);
	m_networkManager->receiveGameUpdatePacket(m_world, m_particleHandler, m_entityHandler);
	m_player->update(camera, m_particleHandler, m_world, m_networkManager, m_inputManager, _deltaTime);
	m_particleHandler.update(_deltaTime);
	m_networkManager->sendPositionDataToServer(camera);
}

void Game::render() {
	// Rendering gameplay
	m_world->render(camera);
	m_blockOutline.render(m_player, camera);
	m_particleHandler.render(camera);
	m_entityHandler.render(camera);
	m_cubeMap.render(camera.getProjectionMatrix(), camera.getViewMatrix());
	m_vignette.render();
	m_hud.render();
}

void Game::destroy() {
	m_hud.destroy();
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world->destroy();
	m_cubeMap.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}


void Game::syncGameWithSettings(Settings* _settings){
	m_vignette.setToggle(_settings->isVignetteToggled);
}
