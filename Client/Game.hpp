#ifndef GAME_H
#define GAME_H
#include <SFML/Network.hpp>
#include <GL/glew.h>
#include <glm/gtc/noise.hpp>
#include "InputManager.hpp"
#include "Player.hpp"
#include "ChunkShader.hpp"
#include "World.hpp"
#include "CubeMap.hpp"
#include "ParticleRenderer.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "GUIHandler.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include <thread>


class Game {
public:

     void init(GUIFont* font, sf::IpAddress ip);
     void update(Settings& settings, float deltaTime, GameStates& state, Player& player);
     void render(Settings& settings, Player& player, float deltaTime);
     void destroy();

     //Game functions
     void generateColorVector(std::vector<vec3>& colors);
     void generateLocalWorld();

     World world;
     std::vector<vec3> colors;

private:

     //Game functions
     void connectToServer(sf::IpAddress& ip);
     void receiveAndDecompressWorld();
     void receivePacket();
     void initGUI();
     void calcFps();
     void updateCameraAndWorld(Settings& settings, float deltaTime);

     //Engine Variables
     CubeMap m_cubeMap;
     ParticleRenderer m_particleRenderer;
     GUIHandler m_handler;
     Camera m_camera;


     //Game Variables
     std::unordered_map<uint8_t, uint8_t> m_clients;
     std::string m_fpsString;
     unsigned int m_fps;
     sf::Clock m_fpsClock;
     sf::TcpSocket m_socket;


};

#endif
