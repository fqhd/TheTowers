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
#include <GL/glew.h>
#include "Engine/Utils/CubeMap.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "GameStates.hpp"
#include "Engine/Utils/Camera.hpp"
#include "BlockOutline.hpp"
#include "Engine/GUI/GUIHandler.hpp"
#include "Config.hpp"


class Game {
public:

	void init(InputManager* _manager, sf::IpAddress& _ip, Config& _c, TextureArray* _textureArray, GUIFont* _font);
	void update(GameStates& _state, Player& _player, float _deltaTime);
	void render(Player& _player);
	void destroy();

private:

	void addGUI();

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	Camera m_camera;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	World m_world;
	NetworkManager m_networkManager;
	InputManager* m_inputManager;
	TextureArray* m_textureArray;
	GUIHandler m_guiHandler;

	//Game Variables
	sf::Clock m_msPerFramePrintClock;


};

#endif
