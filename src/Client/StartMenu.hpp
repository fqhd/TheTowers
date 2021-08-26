#pragma once

#include "InputManager.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "Config.hpp"
#include "GUIRenderer.hpp"
#include "GUIInput.hpp"
#include <SFML/Network/IpAddress.hpp>

class StartMenu  {
public:

    void init(InputManager *inputManager, 
              Window *window,
              GUIRenderer *guiRenderer,
              Config *config,
              Timer *deltaTimer);
    void loop();
	sf::IpAddress getIp();
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
	sf::IpAddress m_ip;
};