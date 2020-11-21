#pragma once
#include "Shader.hpp"
#include <glm/glm.hpp>
#include "Vertex.hpp"

class GUIFontShader : public Shader {
public:


	//Loading Functions
	void loadMatrix(const glm::mat4& matrix);
	void loadColor(const ColorRGBA8& color);

	void getUniformLocations();
	

private:




	//Uniforms
	GLint m_matrixLocation;
	GLint m_colorLocation;

};
