#include "GUIHandler.hpp"
#include "../../../Constants.hpp"

void GUIHandler::init(GUIFont* font){

	m_font = font;

	m_guiRenderer.init();
	m_guiShader.init();
	m_fontShader.init();

	m_matrix = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

}

void GUIHandler::update() {

}

void GUIHandler::render() {
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}
	for(auto& i : textMeshes){
		if(i.needsMeshUpdate) m_font->updateMesh(i);
		i.render();
	}
	
}

void GUIHandler::destroy(){
	m_fontShader.destroy();
	m_guiShader.destroy();
	m_guiRenderer.destroy();
}
