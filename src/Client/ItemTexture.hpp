#pragma once

#include "Vec4.hpp"
#include "ItemID.hpp"
#include <GL/glew.h>

class ItemTexture {
public:

	void init();
	math::vec4 getUVQuadFromItemID(ItemID _id) const;
	GLuint getTextureID() const;
	void destroy();

private:

	void populateUVQuadsArray();
	math::vec4 m_uvQuads[128];
	GLuint m_textureID = 0;

};
