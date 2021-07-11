#pragma once

#include "Cube.hpp"
#include "CubeMapShader.hpp"

class CubeMap {
public:

	void init();
	void render(const glm::mat4& projection, const glm::mat4& view);
	void destroy();

private:

  Cube m_cube;
  CubeMapShader m_shader;

};
