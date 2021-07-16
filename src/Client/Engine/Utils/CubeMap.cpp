#include "CubeMap.hpp"
#include <iostream>

void CubeMap::init() {
	m_cube.init();
	m_shader.init();
}

void CubeMap::render(const math::mat4& projection, math::mat4 _view) {
	_view.m[3][0] = 0;
	_view.m[3][1] = 0;
	_view.m[3][2] = 0;
	
	glDepthFunc(GL_LEQUAL);
	m_shader.bind();

	m_shader.loadProjection(projection);
	m_shader.loadView(_view);

	m_cube.render();

	m_shader.unbind();
	glDepthFunc(GL_LESS);
}

void CubeMap::destroy() {
	m_cube.destroy();
	m_shader.destroy();
}
