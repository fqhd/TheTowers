#include "GUIHandler.hpp"
#include "Constants.hpp"

void GUIHandler::init(){

	m_guiRenderer.init();
	m_guiShader.init();
	m_fontShader.init();

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
	renderGUI();
	renderFonts();
}

void GUIHandler::renderFonts(){

	m_fontShader.bind();
	m_fontShader.loadMatrix(m_matrix);

	for(auto& i : textMeshes){
		if(i.needsUpdate){
			fonts.at(i.getFontIndex()).updateMesh(i);
			m_fontShader.loadColor(i.color);
			fonts.at(i.getFontIndex()).bindTexture();
			i.render();
			fonts.at(i.getFontIndex()).unbindTexture();
		}
	}

	m_fontShader.unbind();
}

void GUIHandler::renderGUI(){

	//Preaparing renderer for drawing
	m_guiRenderer.begin();

	//Batching images
	for(auto& i : images){
		i.render(m_guiRenderer);
	}

	//Batching Buttons
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}

	//Batching checkboxes
	for(auto& i : checkboxes){
		i.render(m_guiRenderer);
	}

	for(auto& i : sliders){
		i.render(m_guiRenderer);
	}

	for(auto& i : keyboxes){
		i.render(m_guiRenderer);
	}


	m_guiRenderer.end();

	m_guiShader.bind();
	m_guiShader.loadMatrix(m_matrix);

	m_guiRenderer.render();

	m_guiShader.unbind();
}

void GUIHandler::destroy(){
	m_guiShader.destroy();
	m_guiRenderer.destroy();
}
