#include "Hotbar.hpp"

void Hotbar::init() {
	for(auto& i : items){
		i.count = 0;
	}
	m_selectorLocation = 0;
}

void Hotbar::update(){
	m_selectorLocation -= InputManager::getDeltaMouseWheel();
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
