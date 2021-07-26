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

	m_spriteFont.init("res/fonts/minecraft_font.ttf", fontSize, 512, 512);

	math::mat4 ortho = math::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);

	m_shader.load("res/shaders/sprite_vertex_shader.glsl", "res/shaders/sprite_fragment_shader.glsl");
	m_shader.bind();
	m_shader.loadUniform("matrix", ortho);
	m_shader.unbind();
}

void GUIRenderer::begin(){
	m_guiBatch.begin();
	m_textBatch.begin();
}

void GUIRenderer::drawRect(const math::vec4& destRect, const math::vec4& uvRect, GLuint texture, const ColorRGBA8& color){
	m_guiBatch.draw(destRect, uvRect, texture, color);
}

void GUIRenderer::drawText(const std::string& s, const math::vec2& position, const math::vec2& scale, const ColorRGBA8& color){
	m_spriteFont.printFont(m_textBatch, s, position, scale, color);
}

void GUIRenderer::end(){
	m_guiBatch.end();
	m_textBatch.end();
}

void GUIRenderer::render(){
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	m_shader.bind();
	m_shader.loadUniform("isFont", false);
	m_guiBatch.render();
	m_shader.loadUniform("isFont", true);
	m_textBatch.render();
	m_shader.unbind();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GUIRenderer::destroy(){
	m_guiBatch.destroy();
	m_textBatch.destroy();
	m_shader.destroy();
	m_spriteFont.destroy();
	assets.destroy();
}
