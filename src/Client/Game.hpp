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
#include "Engine/Input/Window.hpp"
#include "Engine/Utils/Camera.hpp"
#include "BlockOutline.hpp"


class Game {
public:

	void init(sf::IpAddress ip);
	void update(float deltaTime, GameStates& state, Player& player);
	void render(Player& player);
	void destroy();

private:

	//Game functions
	void generateLocalWorld();
	void sendPositionDataToServer();

	//Game functions
	void connectToServer();
	void receiveAndDecompressWorld();
	void receiveGameUpdatePacket();
	void calcFps(float deltaTime);

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	Camera m_camera;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	World m_world;

	//Game Variables
	sf::Clock m_dataFrequencyTimer;
	sf::IpAddress m_serverIp;
	sf::TcpSocket m_tcpSocket;
	sf::UdpSocket m_udpSocket;
	uint8_t m_id = 0;
	uint8_t* m_data = nullptr;


};

#endif
