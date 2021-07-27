#include "Game.hpp"
#include <cstring>
#include <iostream>


void Game::init(InputManager* _iManager, NetworkManager* _nManager, GUIRenderer* _guiRenderer, BlockTextureHandler* _textureHandler, Config* _config, Settings* _settings) {
	m_settings = _settings;
	m_config = _config;
	m_guiRenderer = _guiRenderer;
	m_networkManager = _nManager;
	m_inputManager = _iManager;

	m_world.init(_textureHandler, _config);
	m_assets.init();
	player.init(_config->getReachDistance());
	m_skybox.init(&m_assets);
	m_particleHandler.init();
	m_camera.init(_iManager);
	m_vignette.init();
	m_entityHandler.init(&m_assets);
	m_blockOutline.init(&m_assets);
	m_packetHandler.init(_nManager, &m_world, &m_particleHandler, &m_entityHandler);
	m_debugMenu.init(_config);
}

void Game::update(GameStates& _state, float _deltaTime) {
	// Switch state if key has been pressed
	if (m_inputManager->isKeyPressed(sf::Keyboard::Escape) || !m_inputManager->hasFocus()) {
		m_inputManager->setMouseVisible(true);
		_state = GameStates::PAUSE;
	}
	m_frameCounter.tick(_deltaTime);
	m_packetHandler.handlePackets();
	m_entityHandler.update(_deltaTime);
	m_camera.update();
	player.update(m_camera, m_particleHandler, &m_world, m_networkManager, m_inputManager, _deltaTime);
	m_camera.setPosition(player.getEyePos());
	m_particleHandler.update(_deltaTime);
	m_networkManager->sendPositionDataToServer(m_camera);
}

void Game::render() {
	// Rendering gameplay
	m_skybox.render(m_camera.getProjectionMatrix(), m_camera.getViewMatrix());
	m_world.render(m_camera);
	if(m_settings->renderOutline) m_blockOutline.render(&player, m_camera);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	if(m_settings->isVignetteToggled) m_vignette.render();
	m_hud.render(m_guiRenderer, m_config);
	if(m_settings->isDebugToggled) m_debugMenu.render(m_guiRenderer, m_frameCounter, player);
}

void Game::destroy() {
	m_assets.destroy();
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_skybox.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}