#pragma once
#include "Shader.hpp"
#include "Math.hpp"


class BlockOutlineShader : public Shader {
public:

	//Public utility functions
	void init();

	//Uniform Loading Functions
	void loadProjectionMatrix(const math::mat4& matrix);
	void loadViewMatrix(const math::mat4& matrix);
	void loadBlockPosition(const math::ivec3& position);

private:

	//Private Functions
	void getUniformLocations();


	//OpenGL Variables
	GLint m_projectionMatrixLocation = 0;
	GLint m_viewMatrixLocation = 0;
	GLint m_blockPositionLocation = 0;

};

 
