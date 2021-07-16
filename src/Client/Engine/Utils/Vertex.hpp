#pragma once
#include <GL/glew.h>
#include "../Math/Math.hpp"
#include "ColorRGBA8.hpp"

struct GUITextVertex {
	GUITextVertex(const math::vec2& p, const math::vec2& u){
		position = p;
		uv = u;
	}
	math::vec2 position;
	math::vec2 uv;
};

struct GUIVertex {
	GUIVertex(const math::vec2& p, const ColorRGBA8& c, const math::vec2& tInfo){
		position = p;
		color = c;
		textureInfo = tInfo;
	}
	math::vec2 position;
	ColorRGBA8 color;
	math::vec2 textureInfo;
};
