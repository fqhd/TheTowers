#include "GUIImageRenderer.hpp"

void GUIImageRenderer::init(){
    m_shader.init();

    glm::mat4 matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    m_shader.bind();
    m_shader.loadMatrix(matrix);
    m_shader.unbind();
}

void GUIImageRenderer::renderImage(unsigned int _imageID){
    m_shader.bind();

    m_shader.loadPosition(i.position);
    images[_imageID].render();

    m_shader.unbind();
}

void GUIImageRenderer::destroy(){
    for(auto& i : images){
        i.destroy();
    }
	for(auto i : textures){
		glDeleteTextures(1, &i);
    }
    m_shader.destroy();
}

GLuint GUIImageRenderer::loadTexture(const std::string& path){
	Image image;
	image.loadFromFile(path);

	GLuint tID;
	glGenTextures(1, &tID);
	glBindTexture(GL_TEXTURE_2D, tID);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

	glBindTexture(GL_TEXTURE_2D, 0);

	image.free();

	return tID;
}
