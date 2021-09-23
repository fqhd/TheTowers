#pragma once

#include <cstdint>
#include "Item.hpp"
#include "InputManager.hpp"

class Hotbar {
public:

	void init();
	void update();

	int getSelectorLocation();
	const Item& getSelectedItem();
	Item items[11];

private:
	int m_selectorLocation = 0;

};
