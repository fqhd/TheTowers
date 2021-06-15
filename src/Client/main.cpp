#include "Program.hpp"
#include <iostream>

sf::IpAddress getIP(){
	std::string s;
	std::cout << "Enter server IP: ";
	std::cin >> s;
	sf::IpAddress ip = s;;
	return ip;
}

int main(){

	//Seeding the random function to be completely random each time
	srand(time(0));

	//Getting the ip of the server the client desires to connect to
	sf::IpAddress ip = getIP();

	//Running the game with that requested ip
	Program p;
	p.run(ip);

	return 0;
}

