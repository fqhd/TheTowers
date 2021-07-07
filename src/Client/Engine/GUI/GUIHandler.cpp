#include "GUIHandler.hpp"

void GUIHandler::init(GUIFont* font){
	m_font = font;

	m_guiRenderer.init();
	m_guiShader.init();
	m_fontShader.init();

	m_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
}

void GUIHandler::update(InputManager* _manger) {
	for(auto& i : buttons){
		i.update(_manger);
	}
	for(auto& i : checkboxes){
		i.update(_manger);
	}
}

void GUIHandler::render() {
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}
	for(auto& i : checkboxes){
		i.render(m_guiRenderer);
	}
	for(auto& i : rects){
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
