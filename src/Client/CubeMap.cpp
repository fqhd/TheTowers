#include "CubeMap.hpp"
#include <iostream>

void CubeMap::init(Assets* _assets) {
	m_assets = _assets;
	m_shader.load("res/shaders/cubemap_vertex_shader.glsl", "res/shaders/cubemap_fragment_shader.glsl");
}

void CubeMap::render(const math::mat4& _projection, math::mat4 _view) {
	_view.m[3][0] = 0;
	_view.m[3][1] = 0;
	_view.m[3][2] = 0;
	
	glDepthFunc(GL_LEQUAL);
	m_shader.bind();

	m_shader.loadUniform("projection", _projection);
	m_shader.loadUniform("view", _view);

	glDisable(GL_CULL_FACE);
	m_assets->getCube().render(0, 6);
	glEnable(GL_CULL_FACE);

	m_shader.unbind();
	glDepthFunc(GL_LESS);
}

void CubeMap::destroy() {
	m_shader.destroy();
}
