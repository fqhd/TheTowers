#pragma once

#include "ParticleHandler.hpp"
#include "Camera.hpp"
#include "TTConfig.hpp"
#include <net/net.hpp>

class NetworkManager : public olc::net::client_interface<GameMsg> {
public:

	void connectToServer(const std::string& ip);
	void update();

private:


};
