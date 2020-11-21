#pragma once
#include <GL/glew.h>
#include <SFML/Graphics.hpp>


class Window {
public:

    void init();
    void clear();
    void update();
    void close();

    
    sf::Window window;

private:


};