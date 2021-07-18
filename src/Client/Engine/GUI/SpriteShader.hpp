#pragma once

#include "../Utils/Shader.hpp"
#include "../Math/Math.hpp"


class SpriteShader : public Shader {
public:

	void init();

	void loadMatrix(const math::mat4& _matrix);
	void loadIsFont(bool _isFont);


private:

	void getUniformLocations();
	//Uniforms
	GLint m_matrixLocation = 0;
	GLint m_isFontLocation = 0;


};
