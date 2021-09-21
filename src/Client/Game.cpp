#include "Game.hpp"
#include <cstring>
#include <iostream>


void chunkMeshUpdater(WorkerThreadData* _threadData){
	while(*_threadData->state != GameStates::EXIT){
		_threadData->world->updateMeshes();
		std::this_thread::sleep_for(std::chrono::duration<float>(0.02f));
	}
}

void Game::init(NetworkManager* _nManager, Config* _config, Settings* _settings, GameStates* _state) {
	m_settings = _settings;
	m_config = _config;
	m_networkManager = _nManager;
	m_state = _state;

	m_blockTextureHandler.loadBlockTexturesFromFile();
	m_textureArray.init("res/textures/sprite_sheet.png", 512);
	m_world.init(&m_textureArray, _config, &m_blockTextureHandler);
	player.init(&m_camera, &m_particleHandler, &m_world, _nManager);
	m_skybox.init();
	m_particleHandler.init(&m_textureArray, &m_blockTextureHandler);
	m_camera.init(_config);
	m_vignette.init();
	m_entityHandler.init();
	m_blockOutline.init();
	m_packetHandler.init(_nManager, &m_world, &m_particleHandler, &m_entityHandler);
	m_debugMenu.init(_config);
	m_hud.init(&player.hotbar);

	m_camera.setPosition(player.getEyePos());
	m_camera.updateViewMatrix();

	m_workerThreadData = new WorkerThreadData;
	m_workerThreadData->world = &m_world;
	m_workerThreadData->state = _state;
	m_chunkUpdaterThread = new std::thread(chunkMeshUpdater, m_workerThreadData);
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

void Game::update(float _deltaTime) {
	// Switch state if key has been pressed
	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE) || !InputManager::hasFocus()) {
		InputManager::setMouseGrabbed(false);
		*m_state = GameStates::PAUSE;
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
	m_vignette.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_skybox.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
	m_chunkUpdaterThread->join();
	delete m_chunkUpdaterThread;
	delete m_workerThreadData;
}
