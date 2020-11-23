#include "Window.hpp"
#include "Constants.hpp"

void Window::init(){
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.antialiasingLevel = 4;
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BuildBattle", sf::Style::Titlebar | sf::Style::Close, settings);
	glewInit();
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width / 2) - window.getSize().x/2, (sf::VideoMode::getDesktopMode().height / 2) - window.getSize().y/2));
	window.setVerticalSyncEnabled(false);
	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
    window.display();
}

void Window::close(){
    window.close();
}
