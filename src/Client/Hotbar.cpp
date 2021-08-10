#include "Hotbar.hpp"

Hotbar::Hotbar() {
	m_selectorLocation = 0;
}

void Hotbar::update(InputManager* _iManager){
	m_selectorLocation += _iManager->getDeltaMouseWheel();
	if(m_selectorLocation > 10){
		m_selectorLocation = 0;
	}else if(m_selectorLocation < 0){
		m_selectorLocation = 10;
	}
}

int Hotbar::getSelectorLocation(){
	return m_selectorLocation;
}

uint8_t Hotbar::getSelectedBlockID(){
	return (unsigned int)m_items[m_selectorLocation].id;
}