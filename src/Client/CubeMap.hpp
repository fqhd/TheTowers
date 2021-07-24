#pragma once

#include "Assets.hpp"
#include "CubeMapShader.hpp"

class CubeMap {
public:

	void init(Assets* _assets);
	void render(const math::mat4& projection, math::mat4 view);
	void destroy();

private:

	Assets* m_assets = nullptr;
	CubeMapShader m_shader;

};
