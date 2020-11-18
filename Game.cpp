#include "Game.hpp"
#include "Constants.hpp"

void Game::init(GUIFont* font){
	m_world.init();
	m_modelRenderer.init();
	m_cubeMap.init();
	m_player.init();
	m_particleRenderer.init();
	m_handler.init(font);

	//Adding GUI
	m_handler.images.emplace_back(glm::vec4(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 2 - 3, 6, 6), ColorRGBA8(30, 30, 30, 255));


	//Game Functions
	addModels(); // Note to self: This needs optimization. Loading in 1 vao per model. unacceptable.
	generateColorVector(m_colors);

}

void Game::update(sf::Window& window, InputManager& manager, float deltaTime, GameStates& state){
	if(manager.isKeyPressed(sf::Keyboard::Escape)){
		window.setMouseCursorGrabbed(false);
	     window.setMouseCursorVisible(true);
		state = GameStates::PAUSE;	
	}
	
	m_player.update(window, m_colors, m_particleRenderer, manager, m_world, deltaTime);
	m_cubeMap.update();
	m_particleRenderer.update(deltaTime);
	//Updating GUI
	m_handler.update(window, manager);
}

void Game::render(float deltaTime){
	m_cubeMap.render(m_player.camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_player.camera.getViewMatrix())));
	m_world.render(m_player.camera, m_colors);
	m_particleRenderer.render(m_colors[113], m_player.camera);

	//Calculating FPS
	calcFps();

	//Rendering GUI
	m_handler.render();

	//Rendering FPS
	m_handler.renderFont(m_fpsString.c_str(), 200, 200, 1.0f, ColorRGBA8(255, 255, 255, 255));

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

void Game::addModels(){
	m_modelRenderer.models.push_back(Model(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), "res/models/model.obj"));
	m_modelRenderer.models.push_back(Model(Transform(glm::vec3(20, 50, 20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), "res/models/model.obj"));
}
