#pragma once

#include "NetworkManager.hpp"
#include "World.hpp"
#include "ParticleHandler.hpp"
#include "EntityHandler.hpp"

class PacketHandler {
public:

	/*
		void init(NetworkManager* _manager, World* _world, ParticleHandler* _pHandler, EntityHandler* _eHandler);
		void handlePackets();
	*/

private:

	NetworkManager* m_networkManager = nullptr;
	World* m_world = nullptr;
	ParticleHandler* m_particleHandler = nullptr;
	EntityHandler* m_entityHandler = nullptr;

};