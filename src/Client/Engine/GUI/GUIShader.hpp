#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include "../Utils/Shader.hpp"
#include <glm/glm.hpp>


class GUIShader : public Shader {
public:

	void init();

	void loadMatrix(const glm::mat4& matrix);


private:

	void getUniformLocations();
	//Uniforms
	GLint m_matrixLocation = 0;


};

#endif
