#include "Game.hpp"
#include <cstring>
#include <iostream>


void Game::init(NetworkManager* _nManager, Config* _config, Settings* _settings) {
	m_settings = _settings;
	m_config = _config;
	m_networkManager = _nManager;

	m_blockTextureHandler.loadBlockTexturesFromFile();
	m_textureArray.init("res/textures/sprite_sheet.png", 512);

	m_world.init(&m_textureArray, _config, &m_blockTextureHandler);
	m_assets.init();
	player.init(&m_camera, &m_particleHandler, &m_world, _nManager);
	m_skybox.init(&m_assets);
	m_particleHandler.init(&m_textureArray, &m_blockTextureHandler);
	m_camera.init(_config);
	m_vignette.init();
	m_entityHandler.init(&m_assets);
	m_blockOutline.init(&m_assets);
	m_packetHandler.init(_nManager, &m_world, &m_particleHandler, &m_entityHandler);
	m_debugMenu.init(_config);
	m_hud.init(&player.hotbar);

	m_camera.setPosition(player.getEyePos());
	m_camera.updateViewMatrix();
}

void Game::updateEssentials(float _deltaTime){
	m_frameCounter.tick(_deltaTime);
	m_packetHandler.handlePackets();
	m_entityHandler.update(_deltaTime);
	m_camera.setPosition(player.getEyePos());
	m_camera.updateViewMatrix();
	m_particleHandler.update(_deltaTime);
	networkPositionTick();
}

void Game::update(GameStates& _state, float _deltaTime) {
	// Switch state if key has been pressed
	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE) || !InputManager::hasFocus()) {
		InputManager::setMouseGrabbed(false);
		_state = GameStates::PAUSE;
	}
	m_camera.calculateCameraVectors();
	player.update(_deltaTime);
}

void Game::networkPositionTick(){
	float timeBetweenPackets = 1.0 / m_config->getPacketTransmissionFrequency();
	if (m_dataFrequencyTimer.getElapsedTime() >= timeBetweenPackets) {
		m_dataFrequencyTimer.restart();
		m_networkManager->sendPositionDataToServer(m_camera);
	}
}

void Game::render() {
	// Rendering gameplay
	m_skybox.render(m_camera.getProjectionMatrix(), m_camera.getViewMatrix());
	m_world.render(m_camera);
	if(m_settings->renderOutline) m_blockOutline.render(&player, m_camera);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	if(m_settings->isVignetteToggled) m_vignette.render();
	m_hud.render();
	if(m_settings->isDebugToggled) m_debugMenu.render(m_frameCounter, player);
}

void Game::destroy() {
	m_textureArray.destroy();
	m_assets.destroy();
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_skybox.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}
