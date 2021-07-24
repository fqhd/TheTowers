#pragma once

#include "Shader.hpp"
#include "Math.hpp"


class CubeMapShader : public Shader {
public:

	void init();

	//Loading Uniforms
	void loadProjection(const math::mat4& matrix);
	void loadView(const math::mat4& matrix);

private:

	void getUniformLocations();

	//Locations
	GLint m_projectionLocation = 0;
	GLint m_viewLocation = 0;


};


