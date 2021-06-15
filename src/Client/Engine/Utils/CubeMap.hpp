#ifndef CUBE_MAP_H
#define CUBE_MAP_H
#include "Cube.hpp"
#include "CubeMapTexture.hpp"
#include "CubeMapShader.hpp"

class CubeMap {
public:

	void init();
	void update();
	void render(const glm::mat4& projection, const glm::mat4& view);
	void destroy();

private:

  CubeMapTexture m_dayTexture;
  Cube m_cube;
  CubeMapShader m_shader;

};

#endif