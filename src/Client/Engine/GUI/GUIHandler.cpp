#include "GUIHandler.hpp"

void GUIHandler::init(GUIFont* _font, Settings* _settings){
	m_font = _font;

	m_guiRenderer.init();
	m_guiShader.init();
	m_fontShader.init();

	m_matrix = glm::ortho(0.0f, (float)_settings->screenWidth, 0.0f, (float)_settings->screenHeight);
}

void GUIHandler::update(InputManager* _manger, float deltaTime) {
	for(auto& i : buttons){
		i.update(_manger, deltaTime);
	}
	for(auto& i : checkboxes){
		i.update(_manger, deltaTime);
	}
}

void GUIHandler::render() {
	m_guiRenderer.begin();
	for(auto& i : rects){
		i.render(m_guiRenderer);
	}
	for(auto& i : buttons){
		i.render(m_guiRenderer);
	}
	for(auto& i : checkboxes){
		i.render(m_guiRenderer);
	}
	m_guiRenderer.end();
	m_guiShader.bind();
	m_guiShader.loadMatrix(m_matrix);
	m_guiRenderer.render();
	m_guiShader.unbind();

	for(auto& i : labels){
		if(i.needsMeshUpdate) m_font->updateMesh(i);

		m_fontShader.bind();

		m_fontShader.loadMatrix(m_matrix);
		m_fontShader.loadColor(i.color);
		m_fontShader.loadPosition(i.position);
		m_font->bindTexture();

		i.render();

		m_font->unbindTexture();

		m_fontShader.unbind();
	}
}

void GUIHandler::destroy(){
	m_fontShader.destroy();
	m_guiShader.destroy();
	m_guiRenderer.destroy();
}
