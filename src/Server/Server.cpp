#include "Server.hpp"


void Server::start() {
	m_config.loadFromFile();
	generateWorld();

	// Starting threads
	std::thread positionUpdater(&Server::udpThread, this); // Starting packet position thread
	std::thread packetHandler(&Server::tcpThread, this);

	packetHandler.join();
	positionUpdater.join();

	freeWorldData();
}

void Server::tcpThread(){
	// Server variables
	sf::TcpListener listener;
	sf::SocketSelector selector;

	// Starting server
	std::cout << "Listening for connection..." << std::endl;
	listener.listen(m_config.getServerPort());
	selector.add(listener);

	while(!m_isDone){
		if(selector.wait()){ // Wait for event to happen
			if(selector.isReady(listener)){ // Got new connection, so we are going to handle that by creating a new client
				addClient(listener, selector);
			} else { // Got data from a connected client so we are going to send it to all other clients
				sf::Packet receivedPacket;
				unsigned int senderIndex;
				uint8_t code = getReceivedPacket(selector, receivedPacket, senderIndex);

				switch(code){
					case 1: // Disconnect
						disconnectPlayer(selector, senderIndex);
					break;
					case 2: // Block Update
						updateWorldWithBlockUpdatePacket(receivedPacket);
						addCodeToBlockUpdatePacket(receivedPacket);
						sendPacketToOtherClients(receivedPacket, m_clients[senderIndex].id);
					break;
				}
			}
		}
	}
}

void Server::udpThread(){
	//Variables for algorithm
	sf::UdpSocket socket;
	sf::Packet receivedPacket;
	sf::IpAddress remoteIp;
	unsigned short remotePort;

	//Initializing variables
	socket.bind(m_config.getServerPort());
	socket.setBlocking(false);

	while(!m_isDone){
		while(socket.receive(receivedPacket, remoteIp, remotePort) == sf::Socket::Done){
			uint8_t id;
			receivedPacket >> id;
			receivedPacket << id;

			for(auto& i : m_clients){
				if(i.id != id){
					socket.send(receivedPacket, i.socket->getRemoteAddress(), m_config.getClientPort());
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Server::generateWorld(){
	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();
	unsigned int cw = m_config.getChunkWidth();

	// Allocate memory for the world
	m_worldData = static_cast<uint8_t*>(malloc(ww * wl * wh * cw * cw * cw));

	unsigned int maxW = ww * cw;
	unsigned int maxL = wl * cw;

	// Fill in the memory
	for(unsigned int y = 0; y < wh * cw; y++){
		for(unsigned int z = 0; z < wl * cw; z++){
			for(unsigned int x = 0; x < ww * cw; x++){
				if(y < 20){
					m_worldData[(y * maxW * maxL) + (z * maxW) + x] = 5;
				}else if(x == z){
					m_worldData[(y * maxW * maxL) + (z * maxW) + x] = 2;
				}else{
					m_worldData[(y * maxW * maxL) + (z * maxW) + x] = 0;
				}

			}
		}
	}
}

uint64_t Server::createUniqueID() {
	static uint64_t uid;
	return ++uid;
}

bool Server::doesIDExist(uint64_t id){
	/* Client ids are allocated serially so are always in order; we can use a
         * binary search here
         */

        size_t l = 0;
        size_t r = m_clients.size();

        while (l <= r) {
		size_t m = l + (r - l) / 2;

		if (m_clients[m].id == id)
    			return true;
		else if (m_clients[m].id > id)
    			r = m - 1;
		else
    			l = m + 1;
	}
	return false;
}

void Server::addClient(sf::TcpListener& listener, sf::SocketSelector& selector) {
	// Adding new client to list of clients
	Client client;
	listener.accept(*client.socket);
	client.id = createUniqueID();
	m_clients.push_back(client);
	selector.add(*client.socket);

	// Sending chosen ID to client
	sf::Packet packet;
	for (uint8_t i = 0; i < 64; i += 8)
		packet << (uint8_t)(client.id >> i & 0xff);

	client.socket->send(packet);
	packet.clear();
	std::cout << "New client connected with ID: " << client.id << std::endl;
}

void Server::freeWorldData(){
	free(m_worldData);
}

uint8_t Server::getReceivedPacket(sf::SocketSelector& selector, sf::Packet& packet, unsigned int& _senderIndex) {
	for(unsigned int i = 0; i < m_clients.size(); i++){
		if(selector.isReady(*m_clients[i].socket)){
			sf::Socket::Status status = m_clients[i].socket->receive(packet);
			if(status == sf::Socket::Done){ // Got a valid packet
				_senderIndex = i;
				uint8_t code;
				packet >> code;
				return code;
			} else if (status == sf::Socket::Disconnected) { // The client has disconnected
				// We remove the client and send a packet to other clients that a player has disconnected
				_senderIndex = i;
				return 1; // We return 1 because 1 is the code for a disconnect request
			}
		}
	}
	return 0;
}

void Server::disconnectPlayer(sf::SocketSelector& _selector, unsigned int _playerID){
	sf::Packet packet;
	packet.clear();
	packet << (uint8_t)1; // We send the keycode 1 because that is the code for a disconnection

	for (uint8_t i = 0; i < 64; i += 8)
		packet << (uint8_t)(m_clients[_playerID].id >> i & 0xff);

	sendPacketToAllClients(packet);
	std::cout << "Client Disconnected with ID: " << (unsigned int)m_clients[_playerID].id << std::endl;
	_selector.remove(*m_clients[_playerID].socket);
	delete m_clients[_playerID].socket;
	m_clients[_playerID] = m_clients.back();
	m_clients.pop_back();
}

void Server::sendPacketToAllClients(sf::Packet& packet){
	for(auto& i : m_clients){
		i.socket->send(packet);
	}
}

void Server::sendPacketToOtherClients(sf::Packet& packet, uint8_t senderID){
	for(auto& i : m_clients){
		if(i.id != senderID) i.socket->send(packet);
	}
}

void Server::setBlock(int _x, int _y, int _z, uint8_t _block){
	unsigned int maxW = m_config.getWorldWidth() * m_config.getChunkWidth();
	unsigned int maxL = m_config.getWorldLength() * m_config.getChunkWidth();
	m_worldData[(_y * maxW * maxL) + (_z * maxW) + _x] = _block;
}

void Server::updateWorldWithBlockUpdatePacket(sf::Packet& _packet){
	int x = 0;
	int y = 0;
	int z = 0;
	uint8_t block = 0;

	_packet >> x >> y >> z >> block;

	setBlock(x, y, z, block);
}

void Server::addCodeToBlockUpdatePacket(sf::Packet& _packet){
	int x, y, z;
	uint8_t block;

	_packet >> x >> y >> z >> block;
	_packet.clear();
	_packet << (uint8_t)2 << x << y << z << block;
}
