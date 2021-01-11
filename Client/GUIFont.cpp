#define STB_TRUETYPE_IMPLEMENTATION
#include "GUIFont.hpp"
#include "Utils.hpp"

GUIFont::GUIFont(const std::string& fontLocation){

	// Variables
	unsigned int mapWidth = 512;
	unsigned int mapHeight = 512;

	// Allocating data for font loading and bitmap
	m_fontData = Utils::readFileToBuffer(fontLocation);
	uint8_t* bitmapBuffer = new uint8_t[mapWidth * mapHeight];

	//Creating the bitmap
	m_charData = new stbtt_bakedchar[128];
	stbtt_BakeFontBitmap(m_fontData, 0, 32.0f, bitmapBuffer, mapWidth, mapHeight, 0, 128, m_charData);

	//Storing the bitmap into a texture
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mapWidth, mapHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bitmapBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void GUIFont::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void GUIFont::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GUIFont::destroy(){
	Utils::freeBuffer(m_fontData);
	delete[] m_charData;
}

void GUIFont::updateMesh(GUITextMesh& mesh){
	//Going to take the mesh, create a set of vertices based on its string and upload the vertices to the meshes VAO.

	mesh.needsUpdate = false;
}
