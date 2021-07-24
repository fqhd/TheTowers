#pragma once

#include "Entity.hpp"
#include "Camera.hpp"
#include <vector>
#include <unordered_map>
#include <SFML/Network.hpp>
#include "NetworkManager.hpp"
#include "Cube.hpp"
#include "EntityShader.hpp"
#include "Assets.hpp"


class NetworkManager;

class EntityHandler {
public:


	void init(Assets* _assets);
	void update(NetworkManager* _manager, float _deltaTime);
	void render(Camera& camera);
	void destroy();
	void removeEntity(uint8_t entity);


private:

	//Functions
	void addEntity(uint8_t id, const math::vec3& position, float pitch, float yaw);

	//Data Structures
	std::unordered_map<uint8_t, Entity> m_entities;

	Assets* m_assets = nullptr;
	Transform t;
	EntityShader m_shader;

};
