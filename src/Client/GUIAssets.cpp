#include "GUIAssets.hpp"


GLuint GUIAssets::loadTexture(const std::string& _path){
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

GLuint GUIAssets::getTexture(const std::string& _name){
	auto it = m_textureMap.find(_name);
	if(it != m_textureMap.end()){
		// Got the texture
		return it->second;
	}
	// Did not find the texture, must load it
	GLuint id = loadTexture("res/textures/gui/" + _name + ".png");
	m_textureMap[_name] = id;
	return id;
}