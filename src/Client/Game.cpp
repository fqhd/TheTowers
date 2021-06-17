#include "Game.hpp"
#include <cstring>
#include <iostream>
#include <glm/gtc/noise.hpp>
#include "Engine/Input/Window.hpp"
#include "../Constants.hpp"



void Game::init(sf::IpAddress ip) {


	m_networkManager.connectToServer(ip);
	m_cubeMap.init();
	m_particleHandler.init();
	m_camera.init();
	m_entityHandler.init();
	m_blockOutline.init();

}

void Game::update(float deltaTime, GameStates& state, Player& player) {

	//Switch state if key has been pressed
	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE)) {
		Window::setMouseCursorGrabbed(false);
		state = GameStates::PAUSE;
	}

	m_entityHandler.update(m_networkManager, deltaTime);
	m_networkManager.receiveGameUpdatePacket(m_world, m_particleHandler, m_entityHandler);
	m_camera.update(deltaTime);
	player.update(m_camera, m_particleHandler, m_world, m_networkManager);
	m_cubeMap.update();
	m_particleHandler.update(deltaTime);
	m_networkManager.sendPositionDataToServer(m_camera);

}

void Game::render(Player& player) {
	sf::Clock tmp;
	
	tmp.restart();
	m_world.render(m_camera);
	m_blockOutline.render(player, m_camera);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	m_cubeMap.render(m_camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_camera.getViewMatrix())));

	if(m_msPerFramePrintClock.getElapsedTime().asSeconds() >= 1.0f){
		std::cout << "ms: " << tmp.getElapsedTime().asMilliseconds() << std::endl;
		m_msPerFramePrintClock.restart();
	}	

}

void Game::destroy() {
	m_cubeMap.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_cubeMap.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}
