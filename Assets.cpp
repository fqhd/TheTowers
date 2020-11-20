#include "Assets.hpp"

void Assets::init(){
	m_monkey.init("res/models/monkey.obj");
}

Model* Assets::getMonkey(){
	return &m_monkey;
}
