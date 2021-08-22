#include "ItemTexture.hpp"
#include "Utils.hpp"

const unsigned int ITEM_WIDTH = 8; // Width of each item in the item texture
const unsigned int TEXTURE_WIDTH = 256; // Width of item texture

void ItemTexture::init(){
	m_textureID = Utils::loadTexture("res/textures/gui/item_sprite_sheet.png");
	populateUVQuadsArray();
}

void ItemTexture::populateUVQuadsArray(){
	for(unsigned int i = 0; i < NUM_ITEM_UVS; i++){
		m_uvQuads[i] = math::vec4(((i - 1) % (TEXTURE_WIDTH / ITEM_WIDTH)) * ITEM_WIDTH, (i - 1) / (TEXTURE_WIDTH / ITEM_WIDTH), ITEM_WIDTH, ITEM_WIDTH) / TEXTURE_WIDTH;
	}
}

const math::vec4& ItemTexture::getUVQuad(ItemID _id) const {
	return m_uvQuads[(uint8_t)_id];
}

GLuint ItemTexture::getTextureID() const {
	return m_textureID;
}

void ItemTexture::destroy(){
	glDeleteTextures(1, &m_textureID);
}
