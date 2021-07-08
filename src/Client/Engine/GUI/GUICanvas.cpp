#include "GUICanvas.hpp"

GUICanvas::GUICanvas(const glm::vec4& _destRect){
    destRect = _destRect;
}

void GUICanvas::update(InputManager* _manager){
    for(auto& i : buttons){
		i.update(_manger);
	}
	for(auto& i : checkboxes){
		i.update(_manger);
	}
}

void GUICanvas::render(GUIRenderer& _renderer){
    m_guiRenderer.begin();
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
	m_guiRenderer.end();

	m_guiShader.bind();
	m_guiShader.loadMatrix(m_matrix);
	m_guiRenderer.render();
	m_guiShader.unbind();
}

void GUICanvas::updateElementPositions(const glm::vec2& _windowSize){
    // Loops through all elements and calls updateRelativePosition() function
}
