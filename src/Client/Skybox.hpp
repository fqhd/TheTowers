#pragma once

#include "Assets.hpp"
#include "Shader.hpp"

class Skybox {
public:

	void init(Assets* _assets);
	void render(const math::mat4& _projection, math::mat4 view);
	void destroy();

private:

	Assets* m_assets = nullptr;
	Shader m_shader;

};
