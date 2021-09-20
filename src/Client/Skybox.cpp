#include "Skybox.hpp"
#include <iostream>

void Skybox::init() {
	m_cube.init();
	m_shader.load("res/shaders/cubemap_vertex_shader.glsl", "res/shaders/cubemap_fragment_shader.glsl");
}

void Skybox::render(const math::mat4& _projection, math::mat4 _view) {
	_view.m[3][0] = 0;
	_view.m[3][1] = 0;
	_view.m[3][2] = 0;

	m_shader.bind();
	m_shader.loadUniform("projection", _projection);
	m_shader.loadUniform("view", _view);

	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	m_cube.render();
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);

	m_shader.unbind();
}

void Skybox::destroy() {
	m_cube.destroy();
	m_shader.destroy();
}
