#pragma once

#include "Entity.hpp"
#include "Engine/Utils/ModelShader.hpp"
#include "Engine/Utils/Camera.hpp"
#include "Engine/Utils/Model.hpp"
#include <vector>
#include <unordered_map>
#include <SFML/Network.hpp>
#include "NetworkManager.hpp"


class NetworkManager;

class EntityHandler {
public:


	void init();
	void update(NetworkManager* _manager, float _deltaTime);
	void render(Camera& camera);
	void destroy();
	void removeEntity(uint8_t entity);


private:

	//Functions
	void addEntity(uint8_t id, const glm::vec3& position, float pitch, float yaw);

	//Objects
	ModelShader m_shader;
	Model m_model;

	//Data Structures
	std::unordered_map<uint8_t, Entity> m_entities;

};
