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
#include "GUICanvas.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "BlockOutline.hpp"


class Game {
public:

     void init(sf::IpAddress ip, GUICanvas& workspace);
     void update(Settings& settings, float deltaTime, GameStates& state, Player& player, GUICanvas& workspace);
     void render(Settings& settings, Player& player, float deltaTime);
     void destroy();

	void updateGUIElements(Player& player, GUICanvas& workspace, Settings& settings);
     void updateElementsBasedOnResize();



private:

     //Game functions
     void generateColorVector(std::vector<vec3>& colors);
     void generateLocalWorld();
	void sendPositionDataToServer();

     //Game functions
     void connectToServer();
     void receiveAndDecompressPacket();
     void receiveGameUpdatePacket();
     void initGUI(GUICanvas& workspace);
     void calcFps(float deltaTime, GUICanvas& workspace);
     void updateCameraAndWorld(Settings& settings, float deltaTime);

     //Engine Variables
     CubeMap m_cubeMap;
     ParticleHandler m_particleHandler;
     Camera m_camera;
     EntityHandler m_entityHandler;
     BlockOutline m_blockOutline;
	World m_world;


     //Game Variables
     std::unordered_map<uint8_t, uint8_t> m_clients;
     sf::Clock m_fpsClock;
	sf::Clock m_dataFrequencyTimer;
	sf::IpAddress m_serverIp;
     sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	std::vector<vec3> m_colors;
     uint8_t m_id = 0;


};

#endif
