#include "HUD.hpp"

void HUD::init(){
	m_imageRenderer.init();
	addTextures(); // Important to add textures before adding images
	addImages();
}

void HUD::render(){
	m_imageRenderer.renderImage(0); // Rendering the crosshair
	m_imageRenderer.renderImage(1); // Rendering the hotbar
}

void HUD::destroy(){
	m_imageRenderer.destroy();
}

void HUD::addTextures(){
	m_imageRenderer.addTexture("res/textures/gui/crosshair.png");
	m_imageRenderer.addTexture("res/textures/gui/hotbar.png");
	m_imageRenderer.addTexture("res/textures/gui/selector.png");
}

void HUD::addImages(){
	m_imageRenderer.addImage(glm::vec4(952, 532, 16, 16), 0);
	m_imageRenderer.addImage(glm::vec4(724, 4, 472, 52), 1);
}