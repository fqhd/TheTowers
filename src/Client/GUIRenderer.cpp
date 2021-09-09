#include "GUIRenderer.hpp"

SpriteBatch GUIRenderer::m_guiBatch;
SpriteBatch GUIRenderer::m_textBatch;
SpriteFont GUIRenderer::m_spriteFont;
Shader GUIRenderer::m_shader;

void GUIRenderer::init(unsigned int windowWidth, unsigned int windowHeight, GLuint textureID){
	m_spriteFont.init("res/fonts/minecraft_font.ttf", 40, 512, 512);
	m_guiBatch.init(textureID);
	m_textBatch.init(m_spriteFont.getTextureID());

	math::mat4 ortho = math::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);

	m_shader.load("res/shaders/sprite_vertex_shader.glsl", "res/shaders/sprite_fragment_shader.glsl");
	m_shader.bind();
	m_shader.loadUniform("matrix", ortho);
	m_shader.unbind();
}

void GUIRenderer::drawRect(const math::vec4& destRect, const math::vec4& uvRect, const ColorRGBA8& color){
	m_guiBatch.draw(destRect, uvRect, color);
}

void GUIRenderer::drawText(const std::string& s, const math::vec2& position, const math::vec2& scale, const ColorRGBA8& color){
	m_spriteFont.printFont(m_textBatch, s, position, scale, color);
}

void GUIRenderer::batch(){
	m_guiBatch.batch();
	m_textBatch.batch();
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
}
