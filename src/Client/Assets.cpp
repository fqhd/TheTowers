#include "Assets.hpp"


void Assets::init(){
	m_cube.init();
	m_outline.init();
	m_entityModel.init("res/models/monkey.obj");
}

const Cube& Assets::getCube() const {
	return m_cube;
}

const Outline& Assets::getOutline() const {
	return m_outline;
}

const Model& Assets::getModel() const {
	return m_entityModel;
}

void Assets::destroy(){
	m_cube.destroy();
}
