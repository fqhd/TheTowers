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
#include "ParticleHandler.hpp"
#include "GameStates.hpp"
#include "EntityHandler.hpp"
#include "Settings.hpp"
#include "GUIHandler.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "BlockOutline.hpp"


class Game {
public:

     void init(GUIFont* font, sf::IpAddress ip);
     void update(Settings& settings, float deltaTime, GameStates& state, Player& player);
     void render(Settings& settings, Player& player, float deltaTime);
     void destroy();


     void updateElementsBasedOnResize();



private:

     //Game functions
     void generateColorVector(std::vector<vec3>& colors);
     void generateLocalWorld();
	void sendPositionDataToServer();

     //Game functions
     void connectToServer();
     void receiveAndDecompressWorld();
     void receiveBlockUpdate();
     void initGUI();
     void calcFps();
     void updateCameraAndWorld(Settings& settings, float deltaTime);

     //Engine Variables
     CubeMap m_cubeMap;
     ParticleHandler m_particleHandler;
     GUIHandler m_handler;
     Camera m_camera;
     EntityHandler m_entityHandler;
     BlockOutline m_blockOutline;
	World m_world;


     //Game Variables
     std::unordered_map<uint8_t, uint8_t> m_clients;
     std::string m_fpsString;
     unsigned int m_fps;
     sf::Clock m_fpsClock;
	sf::Clock m_dataFrequencyTimer;
	sf::IpAddress m_serverIp;
     sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	std::vector<vec3> m_colors;


};

#endif
