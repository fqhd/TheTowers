#include "Game.hpp"
#include <cstring>
#include <iostream>
#include "FilePathManager.hpp"

void Game::init(NetworkManager* _nManager, Settings* _settings, GameStates* _state) {
	m_settings = _settings;
	m_networkManager = _nManager;
	m_state = _state;

	m_blockTextureHandler.loadBlockTexturesFromFile();
	m_textureArray.init(FilePathManager::getRootFolderDirectory() + "res/textures/sprite_sheet.png", 512);
	m_world.init(&m_textureArray, &m_blockTextureHandler);
	player.init(&m_camera, &m_particleHandler, &m_world, _nManager);
	m_skybox.init();
	m_particleHandler.init(&m_textureArray, &m_blockTextureHandler);
	m_camera.init();
	m_vignette.init();
	m_entityHandler.init();
	m_blockOutline.init();
	m_hud.init(&player.hotbar);
	m_camera.setPosition(player.getEyePos());
}

void Game::updateEssentials(float _deltaTime){
	m_frameCounter.tick(_deltaTime);
	m_entityHandler.update(_deltaTime);
	m_world.updateMeshes();
	m_camera.setPosition(player.getEyePos());
	m_particleHandler.update(_deltaTime);
	networkPositionTick();
}

void Game::update(float _deltaTime) {
	// Switch state if key has been pressed
	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE) || !InputManager::hasFocus()) {
		InputManager::setMouseGrabbed(false);
		*m_state = GameStates::PAUSE;
	}
	m_camera.update();
	player.update(_deltaTime);
}

void Game::networkPositionTick(){
	float timeBetweenPackets = 1.0f / PACKET_TRANSMISSION_FREQUENCY;
	if (m_dataFrequencyTimer.getElapsedTime() >= timeBetweenPackets) {
		m_dataFrequencyTimer.restart();
		// m_networkManager->sendPositionDataToServer(m_camera);
	}
}

void Game::render() {
	// Rendering gameplay
	m_skybox.render(m_camera.getProjectionMatrix(), m_camera.getViewMatrix());
	m_world.render(m_camera);
	m_blockOutline.render(&player, m_camera, m_settings->legacyOutline);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	if(m_settings->isVignetteToggled) m_vignette.render();
	m_hud.render();
	if(m_settings->isDebugToggled) m_debugMenu.render(m_frameCounter, player);
}

void Game::destroy() {
	m_textureArray.destroy();
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_skybox.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}
