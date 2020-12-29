#include "GUIHandler.hpp"
#include "Constants.hpp"

void GUIHandler::init(GUIFont* font){

	m_font = font;
	m_renderer.init();
	m_shader.loadShader("res/shaders/guiVertex.glsl", "res/shaders/guiFragment.glsl");
	m_shader.getUniformLocations();

	m_fShader.loadShader("res/shaders/fontVertex.glsl", "res/shaders/fontFragment.glsl");
	m_fShader.getUniformLocations();
	m_fRenderer.init();

	m_matrix = glm::ortho(0.0f, (float)Constants::getScreenWidth(), 0.0f, (float)Constants::getScreenHeight());

	//Loading matrix and colors
	m_fShader.bind();
	m_fShader.loadMatrix(m_matrix);
	m_fShader.loadColor(ColorRGBA8(255, 255, 255, 255));
	m_fShader.unbind();

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

	for(auto& i : boxes){
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

	for(auto& i : boxes){
		i.render(m_renderer);
	}

	for(auto& i : keyboxes){
		i.render(m_renderer);
	}


	m_renderer.end();


	m_shader.bind();
	m_shader.loadMatrix(m_matrix);

	//Final render
	m_renderer.render();

	m_shader.unbind();
}

void GUIHandler::renderFont(const std::string& text, float x, float y, float scale, const ColorRGBA8& color){
	m_fShader.bind();
	m_fShader.loadMatrix(m_matrix);
	m_fShader.loadColor(color);
	m_fRenderer.render(*m_font, text, x, y, scale);
	m_fShader.unbind();
}

void GUIHandler::destroy(){
	m_fShader.destroy();
	m_fRenderer.destroy();
	m_shader.destroy();
	m_renderer.destroy();
}
