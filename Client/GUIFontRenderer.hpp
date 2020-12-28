#ifndef GUI_FONT_RENDERER_H
#define GUI_FONT_RENDERER_H
#include <GL/glew.h>
#include "GUIFont.hpp"


class GUIFontRenderer{
public:

	void init();
	void render(GUIFont& font, const std::string& text, float x, float y, float scale);
	void destroy();



private:


	GLuint m_vaoID;
	GLuint m_vboID;


};

#endif
