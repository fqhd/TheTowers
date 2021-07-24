#include "CubeMap.hpp"
#include <iostream>

void CubeMap::init(Assets* _assets) {
	m_assets = _assets;
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

	glDisable(GL_CULL_FACE);
	m_assets->getCube().render(0, 6);
	glEnable(GL_CULL_FACE);

	m_shader.unbind();
	glDepthFunc(GL_LESS);
}

void CubeMap::destroy() {
	m_shader.destroy();
}
