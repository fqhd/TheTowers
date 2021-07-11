#include "GUIHandler.hpp"

void GUIHandler::init(GUIFont* _font, TextureArray* _textureArray){
	m_font = _font;

	m_textureArray = _textureArray;
	guiRenderer.init();
	guiShader.init();
	m_fontShader.init();

	glm::mat4 matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

	// Loading the matrix to the guishader
	guiShader.bind();
	guiShader.loadMatrix(matrix);
	guiShader.unbind();

	// Loading the matrix to the fontShader
	m_fontShader.bind();
	m_fontShader.loadMatrix(matrix);
	m_fontShader.unbind();
}

void GUIHandler::destroy(){
	for(unsigned int i = 0; i < m_canvases.size(); i++){
		delete m_canvases[i];
	}
	m_fontShader.destroy();
	guiShader.destroy();
	guiRenderer.destroy();
}

GUICanvas* GUIHandler::createCanvas(){
	GUICanvas* canvas = new GUICanvas(&guiRenderer, &guiShader, m_font, &m_fontShader, m_textureArray);
	m_canvases.push_back(canvas);
	return canvas;
}
