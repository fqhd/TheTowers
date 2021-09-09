#include "GUIAssets.hpp"
#include "Utils.hpp"

std::unordered_map<std::string, GLuint> GUIAssets::m_textureMap;

GLuint GUIAssets::getTexture(const std::string& _name){
	return 0;
	auto it = m_textureMap.find(_name);
	if(it != m_textureMap.end()){
		// Got the texture
		return it->second;
	}
	// Did not find the texture, must load it
	GLuint id = Utils::loadTexture("res/textures/gui/" + _name + ".png");
	m_textureMap[_name] = id;
	return id;
}

void GUIAssets::destroy(){
	for(auto it = m_textureMap.begin(); it != m_textureMap.end(); it++){
		glDeleteTextures(1, &it->second);
	}
}
