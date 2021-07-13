#include "Hotbar.hpp"

const float HEIGHT = (38 - 32) + 64;
const float WIDTH = 9 * HEIGHT;

void Hotbar::render(GUIRenderer& _renderer){
    _renderer.draw(math::vec4(1280/2 - WIDTH/2, 10, WIDTH, HEIGHT), ColorRGBA8(225, 225, 225, 255), 0);
}
