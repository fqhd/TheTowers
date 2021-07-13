#pragma once

#include "Engine/GUI/GUIRenderer.hpp"

class Hotbar {
public:

    void render(GUIRenderer& _renderer);

    uint8_t items[9];
};
