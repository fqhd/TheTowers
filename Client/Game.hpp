#ifndef GAME_H
#define GAME_H
#include <SFML/Network.hpp>
#include <glm/gtc/noise.hpp>
#include "Engine/Input/InputManager.hpp"
#include "Player.hpp"
#include "Engine/Utils/ChunkShader.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Libs/glad.h"
#include "Engine/Utils/CubeMap.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "GameStates.hpp"
#include "EntityHandler.hpp"
#include "Settings.hpp"
#include "Engine/GUI/GUICanvas.hpp"
#include "Engine/Input/Window.hpp"
#include "Engine/Utils/Camera.hpp"
#include "BlockOutline.hpp"


class Game {
public:

	void init(sf::IpAddress ip, GUICanvas& workspace);
	void update(Settings& settings, float deltaTime, GameStates& state, Player& player, GUICanvas& workspace);
	void render(Settings& settings, Player& player, float deltaTime);
	void destroy();

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

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	Camera m_camera;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	World m_world;

	//Game Variables
	sf::Clock m_fpsClock;
	sf::Clock m_dataFrequencyTimer;
	sf::IpAddress m_serverIp;
	sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	std::vector<vec3> m_colors;
	uint8_t m_id = 0;
	uint8_t* m_data = nullptr;


};

#endif
