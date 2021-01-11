#ifndef GUI_FONT_H
#define GUI_FONT_H

#include <GL/glew.h>
#include <string>
#include "GUITextMesh.hpp"
#include "stb_truetype.h"


class GUIFont {
public:

	GUIFont(const std::string& fontLocation);
	void bindTexture();
	void unbindTexture();
	void updateMesh(GUITextMesh& mesh);
	void destroy();


private:

	unsigned char* m_fontData = nullptr;
	stbtt_bakedchar* m_charData = nullptr;
	GLuint m_textureID = 0;




};

#endif
