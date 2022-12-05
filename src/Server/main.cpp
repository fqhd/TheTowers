#include "TTConfig.hpp"
#include <net/net.hpp>

class Server : public olc::net::server_interface<GameMsg> {
public:

    Server(uint16_t port) : olc::net::server_interface<GameMsg>(port) {

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
