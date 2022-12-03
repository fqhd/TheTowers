#include "Vignette.hpp"

void Vignette::init(){
	m_quad.init();
	m_shader.load("vignette");
}

void Vignette::render(){
	m_shader.bind();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	m_quad.render();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	m_shader.unbind();
}

void Vignette::destroy(){
	m_shader.destroy();
	m_quad.destroy();
}
