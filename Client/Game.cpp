#include "Game.hpp"
#include "Constants.hpp"
#include <cstring>
#include <glm/gtc/noise.hpp>


using namespace std::literals::chrono_literals;

void myFunction(World* world, const std::vector<vec3>& colors){
     Utils::log("updating the chunks");
     world->updateChunks(colors);
     std::this_thread::sleep_for(100ms);
}

void Game::init(GUIFont* font, sf::IpAddress ip){

	connectToServer(ip);
	receiveAndDecompressWorld();
	m_cubeMap.init();
	m_particleRenderer.init();
	m_handler.init(font);
	m_camera.init(glm::vec3((Constants::getLocalWorldWidth() * Constants::getChunkWidth()) / 2, Constants::getChunkWidth(), (Constants::getLocalWorldWidth() * Constants::getChunkWidth()) / 2));
	initGUI();
	generateColorVector(colors);

}



void Game::initGUI(){
	m_handler.images.emplace_back(glm::vec4(Constants::getScreenWidth() / 2 - 4, Constants::getScreenHeight() / 2 - 4, 8, 8), ColorRGBA8(30, 30, 30, 255));
	m_handler.images.emplace_back(glm::vec4(Constants::getScreenWidth() / 2 - 3, Constants::getScreenHeight() / 2 - 3, 6, 6), ColorRGBA8(30, 30, 30, 255));
}

void Game::connectToServer(sf::IpAddress& ip){
	sf::Socket::Status status = m_socket.connect(ip, 2000);

	if(status != sf::Socket::Status::Done){
		Utils::log("Game: Failed to connect to server");
	}else{
		Utils::log("Game: Connected to server");
	}
}

void Game::receiveAndDecompressWorld(){

	//Allocating memory for the world
	uint8_t* data = new uint8_t[Constants::getWorldWidth() * Constants::getWorldWidth() * Constants::getWorldHeight() * Constants::getChunkSize()];

	sf::Packet packet;

	//Receiving the world in a packet
	m_socket.setBlocking(true);
	m_socket.receive(packet);
	m_socket.setBlocking(false);

	sf::Uint64 size = packet.getDataSize();
	Utils::log("Received Packet Size: " + std::to_string(packet.getDataSize()));
	Utils::log("World Compression Ratio: " + std::to_string((1.0f - packet.getDataSize() / (float)(Constants::getWorldWidth() * Constants::getWorldWidth() * Constants::getWorldHeight() * Constants::getChunkSize())) * 100.0f) + "%");

	//Decompressing the world into allocated memory
	sf::Uint8 blockID = 0;
	sf::Uint64 pointer = 0;
	while(packet >> blockID){
		sf::Uint64 numBlocks = 0;
		packet >> numBlocks;
		for(sf::Uint64 i = 0; i < numBlocks; i++){
			data[pointer + i] = blockID;
		}
		pointer += numBlocks;
	}

	//Initializing the world with decompressed data
	world.init(data);


}


void Game::update(Settings& settings, float deltaTime, GameStates& state, Player& player){

	//Switch state if key has been pressed
	if(InputManager::isKeyPressed(GLFW_KEY_ESCAPE)){
		Window::setMouseCursorGrabbed(false);
		state = GameStates::PAUSE;
	}


	receivePacket();
	updateCameraAndWorld(settings, deltaTime);
	player.update(m_camera, settings, colors, m_particleRenderer, world, deltaTime, m_socket);
	m_cubeMap.update();
	m_particleRenderer.update(deltaTime);
	m_handler.update();

     //Updating GUI color
	m_handler.images[1].color = ColorRGBA8(colors[player.selectedBlock].r, colors[player.selectedBlock].g, colors[player.selectedBlock].b, 255);


}

void Game::receivePacket(){
	sf::Packet packet;

	if(m_socket.receive(packet) == sf::Socket::Done){

		uint8_t x;
		uint8_t y;
		uint8_t z;
		uint8_t b;
		packet >> x >> y  >> z >> b;

		world.setBlock((int)x, (int)y, (int)z, b);

	}
}

void Game::render(Settings& settings, Player& player, float deltaTime){

	m_cubeMap.render(m_camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_camera.getViewMatrix())));
	world.render(settings, m_camera, colors);
	m_particleRenderer.render(m_camera);

	//Calculating FPS
	calcFps();

	//Rendering GUI
	m_handler.render();

	//Rendering FPS
	if(settings.showFPS) m_handler.renderFont(m_fpsString.c_str(), 20, Constants::getScreenHeight() - 48, 1.0f, ColorRGBA8(255, 255, 255, 255));

}

void Game::destroy(){
	world.destroy();
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

void Game::updateCameraAndWorld(Settings& settings, float deltaTime){
	glm::vec3 previousCameraPosition = m_camera.getPosition();
	m_camera.update(settings, deltaTime);
	glm::vec3 currentCameraPosition = m_camera.getPosition();
	world.update(colors, previousCameraPosition, currentCameraPosition);
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
