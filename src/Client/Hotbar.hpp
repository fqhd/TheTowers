#pragma once

#include "Engine/GUI/GUIHandler.hpp"

class Hotbar {
public:

    void render(GUIHandler* _handler);

    uint8_t items[9];
};
