#pragma once

#include "Engine/Utils/Shader.hpp"
#include "Engine/Math/Math.hpp"

class EntityShader : public Shader {
public:

	void init();
	void loadTeam(bool team);
	void loadProjectionMatrix(const math::mat4& matrix);
	void loadModelMatrix(const math::mat4& matrix);
	void loadViewMatrix(const math::mat4& matrix);

private:

	void getUniformLocations();

	GLint m_teamLocation = 0;
	GLint m_projectionLocation = 0;
	GLint m_modelLocation = 0;
	GLint m_viewLocation = 0;

};