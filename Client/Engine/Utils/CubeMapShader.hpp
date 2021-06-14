#ifndef CUBEMAP_SHADER_H
#define CUBEMAP_SHADER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.hpp"


class CubeMapShader : public Shader {
public:

	void init();

	//Loading Uniforms
	void loadProjection(const glm::mat4& matrix);
	void loadView(const glm::mat4& matrix);

private:

	void getUniformLocations();

	//Locations
	GLint m_projectionLocation = 0;
	GLint m_viewLocation = 0;


};

#endif
