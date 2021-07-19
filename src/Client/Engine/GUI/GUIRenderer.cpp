#include "GUIRenderer.hpp"

void GUIRenderer::init(){
	assets.init();
	m_guiBatch.init();
	m_textBatch.init();

	m_spriteFont.init("res/fonts/berlin.ttf", 72.0f, 512, 512);

	math::mat4 ortho = math::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	m_guiShader.init();
	m_guiShader.bind();
	m_guiShader.loadMatrix(ortho);
	m_guiShader.unbind();
}

void GUIRenderer::begin(){
	m_guiBatch.begin();
	m_textBatch.begin();
}

void GUIRenderer::drawRect(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color){
	m_guiBatch.draw(destRect, uvRect, texture, depth, color);
}

void GUIRenderer::drawText(const std::string& s, const math::vec2& position, const ColorRGBA8& color){
	m_spriteFont.printFont(m_textBatch, s, position, color);
}

void GUIRenderer::end(){
	m_guiBatch.end();
	m_textBatch.end();
}

void GUIRenderer::render(){
	m_guiShader.bind();
	glDisable(GL_CULL_FACE);
	m_guiShader.loadIsFont(false);
	m_guiBatch.render();
	m_guiShader.loadIsFont(true);
	glDisable(GL_DEPTH_TEST);
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
