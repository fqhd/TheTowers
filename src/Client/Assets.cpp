#include "Assets.hpp"


void Assets::init(){
	m_cube.init();
}

const Cube& Assets::getCube() const{
	return m_cube;
}

void Assets::destroy(){
	m_cube.destroy();
}
