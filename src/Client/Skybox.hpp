#pragma once

#include "Shader.hpp"
#include "Cube.hpp"

class Skybox {
public:

	void init();
	void render(const math::mat4& _projection, math::mat4 view);
	void destroy();

private:

	Cube m_cube;
	Shader m_shader;

};
