#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.hpp"


class ModelShader : public Shader {
public:



	//Uniform Loading Functions
	void loadProjection(const glm::mat4& matrix);
	void loadView(const glm::mat4& matrix);
	void loadModel(const glm::mat4& matrix);
	void getUniformLocations();
	

private:


	//Uniform locations
	GLint m_projection = 0;
	GLint m_view = 0;
	GLint m_model = 0;



};