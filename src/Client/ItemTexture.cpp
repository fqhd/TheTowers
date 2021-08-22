#include "ItemTexture.hpp"
#include "Utils.hpp"

const unsigned int ITEM_WIDTH = 8; // Width of each item in the item texture
const unsigned int TEXTURE_WIDTH = 256; // Width of item texture

void ItemTexture::init(){
	m_textureID = Utils::loadTexture("res/textures/gui/item_sprite_sheet.png");
}

math::vec4 ItemTexture::getUVQuadFromItemID(ItemID _id) const {
	return math::vec4((((uint8_t)_id - 1) % (TEXTURE_WIDTH / ITEM_WIDTH)) * ITEM_WIDTH, ((uint8_t)_id - 1) / (TEXTURE_WIDTH / ITEM_WIDTH), ITEM_WIDTH, ITEM_WIDTH) / TEXTURE_WIDTH;
}

GLuint ItemTexture::getTextureID() const {
	return m_textureID;
}

void ItemTexture::destroy(){
	glDeleteTextures(1, &m_textureID);
}
