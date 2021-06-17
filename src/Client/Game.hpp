#ifndef GAME_H
#define GAME_H
#include <SFML/Network.hpp>
#include <glm/gtc/noise.hpp>
#include "EntityHandler.hpp"
#include "Engine/Input/InputManager.hpp"
#include "Player.hpp"
#include "Engine/Utils/ChunkShader.hpp"
#include "NetworkManager.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Libs/glad.h"
#include "Engine/Utils/CubeMap.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "GameStates.hpp"
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

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	Camera m_camera;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	World m_world;
	NetworkManager m_networkManager;

	//Game Variables
	sf::Clock m_msPerFramePrintClock;


};

#endif
