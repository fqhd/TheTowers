#include "TTConfig.hpp"
#include <net/net.hpp>

class Server : public olc::net::server_interface<GameMsg> {
public:

    Server(uint16_t port) : olc::net::server_interface<GameMsg>(port) {

    }

	bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
	{
		// For now we will allow all
		return true;
	}
	
	void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
	{
		std::cout << "Bruh disconnected fr" << std::endl;
	}

	void OnMessage(std::shared_ptr<olc::net::connection<GameMsg>> client, olc::net::message<GameMsg>& msg) override
	{
		std::cout << "Got a message!" << std::endl;
		olc::net::message<GameMsg> message;
		message.header.id = GameMsg::Game_UpdatePlayer;
		message << "George Bush";
		client->Send(message);
	}
};

int main(){
	Server s(SERVER_PORT);
	
	s.Start();

	while(1){
		s.Update(-1, true);
	}
	return 0;
}
