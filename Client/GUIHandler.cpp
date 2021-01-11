#include "GUIHandler.hpp"
#include "Constants.hpp"

void GUIHandler::init(){

	m_renderer.init();
	m_shader.init();

	m_matrix = glm::ortho(0.0f, (float)Constants::getScreenWidth(), 0.0f, (float)Constants::getScreenHeight());

}



void GUIHandler::update(){

	for(auto& i : buttons){
		i.update();
	}

	for(auto& i : checkboxes){
		i.update();
	}

	for(auto& i : sliders){
		i.update();
	}

	for(auto& i : keyboxes){
		i.update(keyboxes);
	}

}

void GUIHandler::render(){


	//Preaparing renderer for drawing
	m_renderer.begin();

	//Batching images
	for(auto& i : images){
		i.render(m_renderer);
	}

	//Batching Buttons
	for(auto& i : buttons){
		i.render(m_renderer);
	}

	//Batching checkboxes
	for(auto& i : checkboxes){
		i.render(m_renderer);
	}

	for(auto& i : sliders){
		i.render(m_renderer);
	}

	for(auto& i : keyboxes){
		i.render(m_renderer);
	}


	m_renderer.end();

	m_shader.bind();
	m_shader.loadMatrix(m_matrix);

	m_renderer.render();

	m_shader.unbind();
}

void GUIHandler::destroy(){
	m_shader.destroy();
	m_renderer.destroy();
}
