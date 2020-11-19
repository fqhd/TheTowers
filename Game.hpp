#pragma once
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/gtc/noise.hpp>
#include "InputManager.hpp"
#include "Player.hpp"
#include "ChunkShader.hpp"
#include "Model.hpp"
#include "ModelShader.hpp"
#include "World.hpp"
#include "CubeMap.hpp"
#include "ModelRenderer.hpp"
#include "ParticleRenderer.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "GUIHandler.hpp"

class Game {
public:

     void init(GUIFont* font);
     void update(sf::Window& window, InputManager& manager, float deltaTime, GameStates& state, uint8_t blockID);
     void render(Settings& settings, float deltaTime);
     void destroy();

     //Game functions
     void addModels();
     void generateColorVector(std::vector<vec3>& colors);


private:

     //Game functions
     void calcFps();

     //Engine Variables
     World m_world;
     Player m_player;
     ModelRenderer m_modelRenderer;
     CubeMap m_cubeMap;
     ParticleRenderer m_particleRenderer;
     GUIHandler m_handler;



     //Game Variables
     std::vector<vec3> m_colors;
     std::string m_fpsString;
     unsigned int m_fps;
     sf::Clock m_fpsClock;
     sf::Clock m_clock;



};
