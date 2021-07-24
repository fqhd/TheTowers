#pragma once

#include "Shader.hpp"
#include "Math.hpp"

class ParticleShader : public Shader {
public:

	void init();

	void loadProjection(const math::mat4& matrix);

private:

	void getUniformLocations();
	GLint m_projectionLocation = 0;

};

