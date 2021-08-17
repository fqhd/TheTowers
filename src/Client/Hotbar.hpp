#pragma once

#include <cstdint>
#include "Item.hpp"
#include "InputManager.hpp"

class Hotbar {
public:

	Hotbar();
	void update(InputManager* _iManager);

	int getSelectorLocation();
	const Item& getSelectedItem();
	Item items[11];

private:
	int m_selectorLocation;
};
