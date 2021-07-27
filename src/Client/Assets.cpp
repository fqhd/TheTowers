#include "Assets.hpp"


void Assets::init(){
	m_cube.init();
	m_outline.init();
}

const Cube& Assets::getCube() const {
	return m_cube;
}

const Outline& Assets::getOutline() const {
	return m_outline;
}

void Assets::destroy(){
	m_cube.destroy();
}
