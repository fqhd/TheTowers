#ifndef GUI_CANVAS_H
#define GUI_CANVAS_H

#include <vector>
#include "GUIButton.hpp"
#include "GUIRect.hpp"
#include "GUICheckbox.hpp"

class GUICanvas {
public:

    GUICanvas(const glm::vec4& _destRect);
    void update(InputManager* _manager);
    void render(GUIRenderer& _renderer);
    void updateElementPositions(const glm::vec2& _windowSize);

    std::vector<GUIButton> buttons;
    std::vector<GUIRect> rects;
    std::vector<GUICheckbox> checkboxes;
    std::vector<GUITextMesh> textMeshes;

    glm::vec4 destRect;

};

#endif
