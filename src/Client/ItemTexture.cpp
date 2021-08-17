#include "ItemTexture.hpp"
#include "Utils.hpp"

const float TEXTURE_WIDTH = 128.0f;

void ItemTexture::init(){
	m_textureID = Utils::loadTexture("res/textures/gui/item_sprite_sheet.png");
	populateUVQuadsArray();
}

math::vec4 ItemTexture::getUVQuadFromItemID(ItemID _id) const {
	return m_uvQuads[(unsigned int)_id - 1];
}

GLuint ItemTexture::getTextureID() const {
	return m_textureID;
}

void ItemTexture::destroy(){
	glDeleteTextures(1, &m_textureID);
}

void ItemTexture::populateUVQuadsArray(){
	int i = 0;
	// Dividing them by the texture width convers them from pixel space to 0-1 space
	m_uvQuads[i++] = math::vec4(0, 0, 8, 8) / TEXTURE_WIDTH;
	m_uvQuads[i++] = math::vec4(8, 0, 8, 8) / TEXTURE_WIDTH;
}
