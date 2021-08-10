#pragma once

#include <cstdint>
#include "Item.hpp"
#include "InputManager.hpp"

class Hotbar {
public:

	Hotbar();
	void update(InputManager* _iManager);

	int getSelectorLocation();
	uint8_t getSelectedBlockID();

private:
	int m_selectorLocation;
	Item m_items[11];
};
