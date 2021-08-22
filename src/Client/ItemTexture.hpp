#pragma once

#include "Vec4.hpp"
#include "ItemID.hpp"
#include <GL/glew.h>

const unsigned int NUM_ITEM_UVS = 128;

class ItemTexture {
public:

	void init();
	const math::vec4& getUVQuad(ItemID _id) const;
	GLuint getTextureID() const;
	void destroy();

private:

	void populateUVQuadsArray();
	math::vec4 m_uvQuads[NUM_ITEM_UVS];
	GLuint m_textureID = 0;

};
