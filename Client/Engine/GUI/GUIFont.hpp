#ifndef GUI_FONT_H
#define GUI_FONT_H

#include "../Libs/glad.h"
#include <string>
#include "GUITextMesh.hpp"
#include "../Libs/stb_truetype.h"


class GUIFont {
public:

	void init(const std::string& fontLocation, float pixelHeight, unsigned int w, unsigned int h, unsigned int firstChar = 32, unsigned int numChars = 95);
	void bindTexture();
	void unbindTexture();
	void updateMesh(GUITextMesh& mesh);
	void destroy();


private:

	void renderQuad(std::vector<GUITextVertex>& vertices, const glm::vec4& destRect, const glm::vec4& uv);

	unsigned int m_bitmapWidth = 0;
	unsigned int m_bitmapHeight = 0;
	stbtt_bakedchar* m_charData = nullptr;
	GLuint m_textureID = 0;




};

#endif
