#include "GUIImageRenderer.hpp"
#include "../Utils/Image.hpp"

void GUIImageRenderer::init(){
    m_shader.init();

    glm::mat4 matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    m_shader.bind();
    m_shader.loadMatrix(matrix);
    m_shader.unbind();
}

void GUIImageRenderer::renderImage(unsigned int _imageID){
	GUIImage& img = m_images[_imageID];
    m_shader.bind();
	
	glBindTexture(GL_TEXTURE_2D, img.getTextureID());

    m_shader.loadPosition(img.getPosition());
    img.render();

	glBindTexture(GL_TEXTURE_2D, 0);

    m_shader.unbind();
}

void GUIImageRenderer::destroy(){
    for(auto& i : m_images){
        i.destroy();
    }
	for(auto i : m_textures){
		glDeleteTextures(1, &i);
    }
    m_shader.destroy();
}

GLuint GUIImageRenderer::loadTexture(const std::string& _path){
	Image image;
	image.loadFromFile(_path);

	GLuint tID;
	glGenTextures(1, &tID);
	glBindTexture(GL_TEXTURE_2D, tID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

	glBindTexture(GL_TEXTURE_2D, 0);

	image.free();

	return tID;
}

void GUIImageRenderer::addImage(const glm::vec4& _destRect, unsigned int _index){
	m_images.push_back(GUIImage(_destRect, m_textures[_index]));
}

void GUIImageRenderer::addTexture(const std::string& _path){
	m_textures.push_back(loadTexture(_path));
}