#pragma once

#include "InputManager.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "Config.hpp"
#include "GUIRenderer.hpp"
#include "GUIInput.hpp"

class StartMenu  {
public:

    void init(InputManager *inputManager, 
              Window *window,
              GUIRenderer *guiRenderer,
              Config *config,
              Timer *deltaTimer);
    void loop();
private:

    void updateGUI();
    void renderGUI();

    bool m_gameShouldStart;
    Window *m_window;
    GUIRenderer *m_guiRenderer;
    Timer *m_deltaTimer;
    Config *m_config;
    InputManager *m_inputManager;
    GUIInput m_ipinput;
};