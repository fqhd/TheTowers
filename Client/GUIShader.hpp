#pragma once
#include "Shader.hpp"
#include <glm/glm.hpp>

class GUIShader : public Shader {
public:

	//Loading Uniforms
	void loadMatrix(const glm::mat4& matrix);

	void getUniformLocations();

private:

	//Uniforms
	GLint m_matrix;


};
