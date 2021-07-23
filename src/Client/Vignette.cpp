#include "Vignette.hpp"

void Vignette::init(){
	m_quad.init();
	m_quadShader.init();
}

void Vignette::render(){
	m_quadShader.bind();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	m_quad.render();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	m_quadShader.unbind();
}

void Vignette::destroy(){
	m_quadShader.destroy();
	m_quad.destroy();
}
