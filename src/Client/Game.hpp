#pragma once

#include <SFML/Network.hpp>
#include "EntityHandler.hpp"
#include "Player.hpp"
#include "Engine/Input/InputManager.hpp"
#include "Engine/Utils/ChunkShader.hpp"
#include "NetworkManager.hpp"
#include "Engine/World/World.hpp"
#include "Engine/Utils/CubeMap.hpp"
#include "Engine/Utils/ParticleHandler.hpp"
#include "GameStates.hpp"
#include "Engine/Utils/Camera.hpp"
#include "BlockOutline.hpp"
#include "Vignette.hpp"
#include "Settings.hpp"
#include "FrameCounter.hpp"
#include "HUD.hpp"


class Game {
public:

	void init(InputManager* _iManager, World* _world, NetworkManager* _nManager, Player* _player);
	void update(GameStates& _state, float _deltaTime);
	void render();
	void destroy();

	void syncGameWithSettings(Settings* _settings);

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

	// Pointers
	NetworkManager* m_networkManager = nullptr;
	InputManager* m_inputManager = nullptr;
	World* m_world = nullptr;
	Player* m_player = nullptr;

};
