#pragma once

#include "Engine/Utils/VignetteQuad.hpp"
#include "Engine/Utils/VignetteShader.hpp"

class Vignette {
public:

	void init();
	void render(); // Renders a quad with the vignette shader
	void destroy();

private:

	VignetteQuad m_quad;
	VignetteShader m_quadShader;


};
