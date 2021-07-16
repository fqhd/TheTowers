#pragma once

#include "../Utils/Shader.hpp"
#include "../Math/Math.hpp"


class GUIShader : public Shader {
public:

	void init();

	void loadMatrix(const math::mat4& matrix);


private:

	void getUniformLocations();
	//Uniforms
	GLint m_matrixLocation = 0;


};
