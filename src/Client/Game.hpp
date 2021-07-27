#pragma once

#include <SFML/Network.hpp>
#include "EntityHandler.hpp"
#include "Player.hpp"
#include "InputManager.hpp"
#include "NetworkManager.hpp"
#include "World.hpp"
#include "Skybox.hpp"
#include "ParticleHandler.hpp"
#include "GameStates.hpp"
#include "Camera.hpp"
#include "BlockOutline.hpp"
#include "Vignette.hpp"
#include "Settings.hpp"
#include "FrameCounter.hpp"
#include "HUD.hpp"
#include "World.hpp"
#include "PacketHandler.hpp"
#include "BlockTextureHandler.hpp"
#include "DebugMenu.hpp"

class Game {
public:

	void init(InputManager* _iManager, NetworkManager* _nManager, GUIRenderer* _guiRenderer, BlockTextureHandler* _textureHandler, Config* _config, Settings* _settings);
	void update(GameStates& _state, float _deltaTime);
	void render();
	void destroy();

	Player player;

private:

	void renderGUI();

	//Engine Variables
	Camera m_camera;
	FrameCounter m_frameCounter;
	Skybox m_skybox;
	ParticleHandler m_particleHandler;
	EntityHandler m_entityHandler;
	BlockOutline m_blockOutline;
	Vignette m_vignette;
	HUD m_hud;
	Assets m_assets;
	World m_world;
	PacketHandler m_packetHandler;
	DebugMenu m_debugMenu;

	// Pointers
	Settings* m_settings = nullptr;
	Config* m_config = nullptr;
	GUIRenderer* m_guiRenderer = nullptr;
	NetworkManager* m_networkManager = nullptr;
	InputManager* m_inputManager = nullptr;

};
