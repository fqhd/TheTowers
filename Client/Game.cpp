#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cstring>
#include <glm/gtc/noise.hpp>

void Game::init(GUIFont* font, sf::IpAddress ip){

	m_data = new uint8_t[WORLD_SIZE * WORLD_SIZE * WORLD_HEIGHT * CHUNK_SIZE];

	sf::Socket::Status status = m_socket.connect(ip, 2000);

	if(status != sf::Socket::Status::Done){
		std::cout << "failed to connect to server" << std::endl;
	}else{
		std::cout << "connected to server" << std::endl;
	}


	sf::Packet packet;

	m_socket.setBlocking(true);
	m_socket.receive(packet);
	m_socket.setBlocking(false);

	sf::Uint64 size = packet.getDataSize();

	std::cout << "Packet Size Received: " << packet.getDataSize() << std::endl;
	std::cout << "U64 Size: " << size << std::endl;

	sf::Uint8 blockID = 0;
	sf::Uint64 pointer = 0;
	while(packet >> blockID){
		sf::Uint64 numBlocks = 0;
		packet >> numBlocks;
		for(sf::Uint64 i = 0; i < numBlocks; i++){
			m_data[pointer + i] = blockID;
		}
		pointer += numBlocks - 1;
	}

	m_world.init(m_data);
	m_modelRenderer.init();
	m_cubeMap.init();
	m_player.init();
	m_particleRenderer.init();
	m_handler.init(font);
	m_assets.init();

	//Adding GUI
	m_handler.images.emplace_back(glm::vec4(SCREEN_WIDTH / 2 - 4, SCREEN_HEIGHT / 2 - 4, 8, 8), ColorRGBA8(30, 30, 30, 255));
	m_handler.images.emplace_back(glm::vec4(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 2 - 3, 6, 6), ColorRGBA8(30, 30, 30, 255));

	//Game Functions
	generateColorVector(m_colors);
	generateEntityColors();
}

void Game::generateEntityColors(){
	for(unsigned int i = 0; i < 16; i++){
		m_entityColors.push_back(ColorRGBA8(i * 16, 0, 255 - i * 16, 255));
	}
}

void Game::update(sf::Window& window, Settings& settings, InputManager& manager, float deltaTime, GameStates& state, uint8_t blockID){

	sf::Packet packet;

	if(m_socket.receive(packet) == sf::Socket::Done){

		uint8_t x;
		uint8_t y;
		uint8_t z;
		uint8_t b;
		glm::vec3 position;
		uint8_t id;
		packet >> x >> y  >> z >> b >> position.x >> position.y >> position.z >> id;

		while ((id - 1) > m_modelRenderer.entities.size()){
			m_modelRenderer.entities.push_back(Entity(Transform(position, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), m_assets.getMonkey(), m_entityColors[id]));
		}
		m_modelRenderer.entities[id - 1].transform.setPosition(position);

		m_world.setBlock((int)x, (int)y, (int)z, b);
	}

	if(manager.isKeyPressed(sf::Keyboard::Escape)){
		window.setMouseCursorGrabbed(false);
	     window.setMouseCursorVisible(true);
		state = GameStates::PAUSE;
	}

	m_player.update(window, settings, m_colors, m_particleRenderer, manager, m_world, deltaTime, blockID, m_socket);
	m_cubeMap.update();
	m_particleRenderer.update(deltaTime);
	//Updating GUI
	m_handler.update(window, manager);

	if(m_networkBufferClock.getElapsedTime().asSeconds() >= 0.2f){
		packet.clear();

		packet << (uint8_t)0 << (uint8_t)0 << (uint8_t)0 << (uint8_t)0 << m_player.position.x << m_player.position.y << m_player.position.z;

		m_socket.send(packet);

		m_networkBufferClock.restart();
	}

	m_handler.images[1].color = ColorRGBA8(m_colors[blockID].r, m_colors[blockID].g, m_colors[blockID].b, 255);

}

void Game::generateLocalWorld(){
	for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_SIZE; z++){
		for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_SIZE; x++){

			float height = (glm::perlin(glm::vec2(x / (float)CHUNK_WIDTH * WORLD_SIZE, z / (float)CHUNK_WIDTH * WORLD_SIZE)) + 1) / 2.0f;

			for(unsigned int i = 0; i < height * CHUNK_WIDTH * WORLD_HEIGHT; i++){
				m_data[(i * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = i + 100;
			}


		}
	}
}

void Game::render(Settings& settings, float deltaTime){
	m_cubeMap.render(m_player.camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_player.camera.getViewMatrix())));
	m_world.render(m_player.camera, m_colors, settings.range);
	m_modelRenderer.render(m_player.camera);
	m_particleRenderer.render(m_player.camera);

	//Calculating FPS
	calcFps();

	//Rendering GUI
	m_handler.render();

	//Rendering FPS
	if(settings.showFPS) m_handler.renderFont(m_fpsString.c_str(), 20, SCREEN_HEIGHT - 48, 1.0f, ColorRGBA8(255, 255, 255, 255));

	//Capping FPS
	if(!settings.vsync){
		float waitTime = 1.0f / settings.maxFps;
		while(m_clock.getElapsedTime().asSeconds() < waitTime){

		}
		m_clock.restart();
	}


}

void Game::destroy(){
	m_world.destroy();
	m_modelRenderer.destroy();
	m_cubeMap.destroy();
	m_particleRenderer.destroy();
}

void Game::calcFps(){
	m_fps++;
	if(m_fpsClock.getElapsedTime().asSeconds() >= 1.0f){
		m_fpsString = std::to_string(m_fps);
		m_fps = 0;
		m_fpsClock.restart();
	}
}

void Game::generateColorVector(std::vector<vec3>& colors){

	for(unsigned int b = 0; b < 6; b++){
		for(unsigned int g = 0; g < 6; g++){
			for(unsigned int r = 0; r < 6; r++){
				colors.push_back(vec3(r * 42, g * 42, b * 42));
			}
		}
	}

}
