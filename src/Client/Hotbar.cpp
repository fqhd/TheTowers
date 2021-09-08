#include "Hotbar.hpp"

void Hotbar::init(InputManager* _manager) {
	for(auto& i : items){
		i.count = 0;
	}
	m_inputManager = _manager;
	m_selectorLocation = 0;
}

void Hotbar::update(){
	m_selectorLocation -= m_inputManager->getDeltaMouseWheel();
	if(m_selectorLocation > 10){
		m_selectorLocation = 0;
	}else if(m_selectorLocation < 0){
		m_selectorLocation = 10;
	}
}

int Hotbar::getSelectorLocation(){
	return m_selectorLocation;
}

const Item& Hotbar::getSelectedItem(){
	return items[m_selectorLocation];
}
