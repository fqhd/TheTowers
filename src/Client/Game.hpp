#pragma once

#include <SFML/Network.hpp>
#include "EntityHandler.hpp"
#include "Player.hpp"
#include "InputManager.hpp"
#include "NetworkManager.hpp"
#include "World.hpp"
#include "CubeMap.hpp"
#include "ParticleHandler.hpp"
#include "GameStates.hpp"
#include "Camera.hpp"
#include "BlockOutline.hpp"
#include "Vignette.hpp"
#include "Settings.hpp"
#include "FrameCounter.hpp"
#include "HUD.hpp"


class Game {
public:

	void init(InputManager* _iManager, World* _world, NetworkManager* _nManager, GUIRenderer* _guiRenderer, Config* _config, Settings* _settings);
	void update(GameStates& _state, float _deltaTime);
	void render();
	void destroy();

	Player player;
	Camera camera;
	FrameCounter frameCounter;

private:

	void renderGUI();

	//Engine Variables
	CubeMap m_cubeMap;
	ParticleHandler m_particleHandler;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	Vignette m_vignette;
	HUD m_hud;
	Assets m_assets;

	// Pointers
	Settings* m_settings = nullptr;
	Config* m_config = nullptr;
	GUIRenderer* m_guiRenderer = nullptr;
	NetworkManager* m_networkManager = nullptr;
	InputManager* m_inputManager = nullptr;
	World* m_world = nullptr;
	Player* m_player = nullptr;

};
