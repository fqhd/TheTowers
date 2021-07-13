#pragma once

#include "Engine/GUI/GUICanvas.hpp"

class Hotbar {
public:

    void render(GUICanvas* _canvas);

    uint8_t items[9];
};
