#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

enum Relative {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    CENTER
};

struct RelativePosition {
    Relative h = CENTER;
    Relative v = CENTER;
};

class GUIElement {
public:

    updateRelativePosition(const glm::vec2& _windowSize);

protected:

    bool absolutelyPositioned = false;
    RelativePosition rPos;
    glm::vec4 destRect;
    ColorRGBA8 color;

};

#endif
