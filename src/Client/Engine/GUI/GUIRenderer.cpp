#include "GUIRenderer.hpp"

void GUIRenderer::init(unsigned int windowWidth, unsigned int windowHeight){
	assets.init();
	m_guiBatch.init();
	m_textBatch.init();

	// Calculating the font size based on window size
	float fontSize = (windowHeight / 1080.0f) * 64.0f;
	// Caping the font size
	if(fontSize > 64.0f){
		fontSize = 64.0f;
	}

	m_spriteFont.init("res/fonts/berlin.ttf", fontSize, 512, 512);

	math::mat4 ortho = math::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);

	m_guiShader.init();
	m_guiShader.bind();
	m_guiShader.loadMatrix(ortho);
	m_guiShader.unbind();
}

void GUIRenderer::begin(){
	m_guiBatch.begin();
	m_textBatch.begin();
}

void GUIRenderer::drawRect(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, const ColorRGBA8& color){
	m_guiBatch.draw(destRect, uvRect, texture, color);
}

void GUIRenderer::drawText(const std::string& s, const math::vec2& position, const ColorRGBA8& color){
	m_spriteFont.printFont(m_textBatch, s, position, color);
}

void GUIRenderer::end(){
	m_guiBatch.end();
	m_textBatch.end();
}

void GUIRenderer::render(){
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	m_guiShader.bind();
	m_guiShader.loadIsFont(false);
	m_guiBatch.render();
	m_guiShader.loadIsFont(true);
	m_textBatch.render();
	m_guiShader.unbind();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GUIRenderer::destroy(){
	m_guiBatch.destroy();
	m_textBatch.destroy();
	m_guiShader.destroy();
	m_spriteFont.destroy();
}
