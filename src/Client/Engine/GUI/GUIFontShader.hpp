#pragma once

#include "../Utils/Shader.hpp"
#include "../Utils/Vertex.hpp"
#include "../Math/Math.hpp"

class GUIFontShader : public Shader {
public:

	void init();

	//Loading Functions
	void loadMatrix(const math::mat4& matrix);
	void loadColor(const ColorRGBA8& color);
	void loadPosition(const math::vec2& position);

private:

	void getUniformLocations();

	//Uniforms
	GLint m_matrixLocation = 0;
	GLint m_colorLocation = 0;
	GLint m_positionLocation = 0;

};

