#pragma once

#include "Cube.hpp"
#include "CubeMapShader.hpp"

class CubeMap {
public:

	void init();
	void render(const math::mat4& projection, math::mat4 view);
	void destroy();

private:

  Cube m_cube;
  CubeMapShader m_shader;

};
