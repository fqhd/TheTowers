#pragma once

#include <unordered_map>

class GUIAssets {
public:

    void init(); // Loads all the gui textures from res/textures/gui/

    GLuint getSelector();
    GLuint getHotbar();
    GLuint getCrosshair();

    void destroy(); // Deletes all the loaded gui textures

private:

    GLuint loadTexture(const std::string& path);

    // Texture IDs
    GLuint m_selector = 0;
    GLuint m_hotbar = 0;
    GLuint m_crosshair = 0;
    

};
