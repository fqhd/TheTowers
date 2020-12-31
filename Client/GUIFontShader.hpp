#ifndef GUI_FONT_SHADER_H
#define GUI_FONT_SHADER_H
#include "Shader.hpp"
#include <glm/glm.hpp>
#include "Vertex.hpp"

class GUIFontShader : public Shader {
public:

	void init();

	//Loading Functions
	void loadMatrix(const glm::mat4& matrix);
	void loadColor(const ColorRGBA8& color);



private:

	void getUniformLocations();



	//Uniforms
	GLint m_matrixLocation = 0;
	GLint m_colorLocation = 0;

};

#endif
