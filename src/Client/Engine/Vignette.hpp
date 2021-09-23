#pragma once

#include "VignetteQuad.hpp"
#include "Shader.hpp"

class Vignette {
public:

	void init();
	void render(); // Renders a quad with the vignette shader
	void destroy();

private:

	VignetteQuad m_quad;
	Shader m_shader;


};
