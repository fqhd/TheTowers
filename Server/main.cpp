#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

int main(){

	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;

	std::cout << "Listening for connection" << std::endl;
	listener.listen(2000);
	selector.add(listener);

	while(true){

		if(selector.wait()){
			if(selector.isReady(listener)){
				sf::TcpSocket* socket = new sf::TcpSocket();
				listener.accept(*socket);
				sockets.push_back(socket);
				selector.add(*socket);
			}else{
				for(unsigned int i = 0; i < sockets.size(); i++){
					if(selector.isReady(*sockets[i])){
						sf::Packet packet;
						if(sockets[i]->receive(packet) == sf::Socket::Done){
							for(unsigned int j = 0; j < sockets.size(); j++){
								if(i != j){
									sockets[j]->send(packet);
								}
							}
						}
					}
				}
			}
		}

	}



     return 0;
}
