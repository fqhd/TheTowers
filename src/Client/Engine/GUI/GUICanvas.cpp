#include "GUICanvas.hpp"

GUICanvas::GUICanvas(GUIRenderer* _renderer, GUIShader* _guiShader, GUIFont* _font, GUIFontShader* _fontShader, TextureArray* _textureArray){
    m_font = _font;
    guiRenderer = _renderer;
    guiShader = _guiShader;
    m_fontShader = _fontShader;
    m_textureArray = _textureArray;
}

void GUICanvas::update(InputManager* _manager, float _deltaTime){
    for(auto& i : buttons){
		i.update(_manager, _deltaTime);
	}
	for(auto& i : checkboxes){
		i.update(_manager, _deltaTime);
	}
}

void GUICanvas::render(){
    guiRenderer->begin();
	for(auto& i : rects){
		i.render(guiRenderer);
	}
	for(auto& i : buttons){
		i.render(guiRenderer);
	}
	for(auto& i : checkboxes){
		i.render(guiRenderer);
	}
	guiRenderer->end();
	guiShader->bind();

	m_textureArray->bind();

	guiRenderer->render();

	m_textureArray->unbind();

	guiShader->unbind();

	for(auto& i : labels){
		if(i.needsMeshUpdate) m_font->updateMesh(i);

		m_fontShader->bind();

		m_fontShader->loadColor(i.color);
		m_fontShader->loadPosition(i.position);
		m_font->bindTexture();

		i.render();

		m_font->unbindTexture();

		m_fontShader->unbind();
	}
}
