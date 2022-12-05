#include "NetworkManager.hpp"
#include <iostream>

void NetworkManager::connectToServer(const std::string& ip) {
	if (!Connect(ip, SERVER_PORT)) {
		std::cout << "Failed to connect to IP: " << ip << std::endl;
	}
}

void NetworkManager::update(){
	static int i = 0;
	i++;
	if(i % 60 == 0){
		olc::net::message<GameMsg> ourMessage;
		ourMessage.header.id = GameMsg::Server_GetPing;
		Send(ourMessage);
	}
	if(IsConnected()){
		if(!Incoming().empty()){
			auto msg = Incoming().pop_front().msg;
			switch(msg.header.id){
				case GameMsg::Client_Accepted:
					std::cout << "Server Client Accepted!" << std::endl;
					std::cout << "You're in! :)" << std::endl;
					break;
				case GameMsg::Game_UpdatePlayer:
					std::cout << "Got our packet back bitches" << std::endl;
					std::cout << "And your packet say:" << std::endl;
					std::cout << msg << std::endl;
					break;
			}
		}
	}
	if(i >= 300){
		Disconnect();
	}
}
