#include "CubeMap.hpp"
#include <iostream>

void CubeMap::init() {
	m_cube.init();
	m_shader.init();
}

void CubeMap::render(const glm::mat4& projection, const glm::mat4& _view) {
	glm::mat4 view = _view;
	view[3][0] = 0;
	view[3][1] = 0;
	view[3][2] = 0;
	
	glDepthFunc(GL_LEQUAL);
	m_shader.bind();

	m_shader.loadProjection(projection);
	m_shader.loadView(view);

	m_cube.render();

	m_shader.unbind();
	glDepthFunc(GL_LESS);
}

void CubeMap::destroy() {
	m_cube.destroy();
	m_shader.destroy();
}
