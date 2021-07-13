#pragma once

#include <SFML/Network.hpp>
#include <glm/gtc/noise.hpp>
#include "EntityHandler.hpp"
#include "Engine/Input/InputManager.hpp"
#include "Player.hpp"
#include "Engine/Utils/ChunkShader.hpp"
#include "NetworkManager.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Utils/CubeMap.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "GameStates.hpp"
#include "Engine/Utils/Camera.hpp"
#include "BlockOutline.hpp"
#include "Engine/GUI/GUICanvas.hpp"
#include "Config.hpp"
#include "Vignette.hpp"
#include "Settings.hpp"
#include "FrameCounter.hpp"

class Game {
public:

	void init(InputManager* _manager, sf::IpAddress& _ip, Config& _c, GUICanvas* _canvas, TextureArray* _textureArray);
	void update(GameStates& _state, Player& _player, float _deltaTime);
	void render(Player& _player);
	void destroy();

	void syncGameWithSettings(Settings* _settings);

	Camera camera;
	FrameCounter m_framecounter;

private:

	void addGUI();

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	World m_world;
	NetworkManager m_networkManager;
	InputManager* m_inputManager = nullptr;
	Vignette m_vignette;
	GUICanvas* m_canvas = nullptr;
	//Game Variables
	sf::Clock m_msPerFramePrintClock;


};
