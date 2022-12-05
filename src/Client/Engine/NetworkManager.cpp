#include "NetworkManager.hpp"
#include <iostream>

void NetworkManager::connectToServer(){
	if(Connect("127.0.0.1", SERVER_PORT)){
		std::cout << "NetworkManager: Connected to Server!" << std::endl;
	}else{
		std::cout << "NetworkManager: Failed to connect to Server" << std::endl;
	}
}

void NetworkManager::update(){
	
}
