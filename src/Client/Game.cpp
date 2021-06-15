#include "Game.hpp"
#include <cstring>
#include <glm/gtc/noise.hpp>
#include "Engine/Input/Window.hpp"
#include "../Constants.hpp"



void Game::init(sf::IpAddress ip) {

	Utils::printDividor("Game");
	m_serverIp = ip;
	m_udpSocket.bind(CLIENT_PORT);
	m_udpSocket.setBlocking(false);
	connectToServer();
	receiveAndDecompressWorld();
	m_cubeMap.init();
	m_particleHandler.init();
	m_camera.init();
	m_entityHandler.init();
	m_blockOutline.init();

}

void Game::connectToServer() {
	Utils::log("Connecting...");
	sf::Socket::Status status = m_tcpSocket.connect(m_serverIp, SERVER_PORT);

	if (status != sf::Socket::Status::Done) {
		Utils::log("Game: Failed to connect to server");
	} else {
		sf::Packet packet;
		m_tcpSocket.setBlocking(true);
		m_tcpSocket.receive(packet);
		m_tcpSocket.setBlocking(false);
		packet >> m_id;
		Utils::log("Game: Connected to server with ID: " + std::to_string(m_id));
	}
}

void Game::receiveAndDecompressWorld() {

	//Allocating memory for the world
	m_data = static_cast<uint8_t*> (malloc(WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE));

	sf::Packet packet;

	//Receiving the world in a packet
	m_tcpSocket.setBlocking(true);
	m_tcpSocket.receive(packet);
	m_tcpSocket.setBlocking(false);

	//Printing information
	Utils::log("Received Packet Size: " + std::to_string(packet.getDataSize()));
	Utils::log("World Compression Ratio: " + std::to_string((1.0f - packet.getDataSize() / (float)(WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE)) * 100.0f) + "%");

	uint8_t blockID = 0;
	uint32_t pointer = 0;
	uint32_t numBlocks = 0;
	while (packet >> blockID) {
		packet >> numBlocks;
		for (uint32_t i = 0; i < numBlocks; i++) {
			m_data[pointer + i] = blockID;
		}
		pointer += numBlocks;
	}

	//Initializing the world with decompressed data
	m_world.init(m_data);

}


void Game::update(float deltaTime, GameStates& state, Player& player) {

	//Switch state if key has been pressed
	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE)) {
		Window::setMouseCursorGrabbed(false);
		state = GameStates::PAUSE;
	}

	m_entityHandler.update(m_udpSocket, deltaTime);
	receiveGameUpdatePacket();
	m_camera.update(deltaTime);
	player.update(m_camera, m_particleHandler, m_world, deltaTime, m_tcpSocket);
	m_cubeMap.update();
	m_particleHandler.update(deltaTime);

	sendPositionDataToServer();

}

void Game::sendPositionDataToServer() {
	float timeBetweenPackets = 1.0f / PACKET_TRANSMISSION_FREQUENCY;
	if (m_dataFrequencyTimer.getElapsedTime().asSeconds() >= timeBetweenPackets) {
		m_dataFrequencyTimer.restart();

		// We execute this code only a few times per second
		// This code sends the position and camera angles to the server
		// Which will in turn send it to other connected clients except ourselves
		sf::Packet packet;
		glm::vec3 p = m_camera.getPosition(); // Camera Position
		packet << m_id << p.x << p.y << p.z << m_camera.getPitch() << m_camera.getYaw();
		m_udpSocket.send(packet, m_serverIp, SERVER_PORT);

	}


}

void Game::receiveGameUpdatePacket() {
	sf::Packet packet;

	if (m_tcpSocket.receive(packet) == sf::Socket::Done) {

		uint8_t code = 0;

		packet >> code;
		if (code == 0) { // If the code is 0 then it is a block update packet
			int x = 0;
			int y = 0;
			int z = 0;
			uint8_t b = 0;

			packet >> x >> y >> z >> b;

			Utils::log("Got block update");

			if (!b) {
				m_particleHandler.placeParticlesAroundBlock(x, y, z);
			}
			m_world.setBlock(x, y, z, b);
		} else if (code == 1) { // If the code is not 0 then a client has disconnected
			uint8_t id = 0;
			packet >> id;
			Utils::log("Person: " + std::to_string(id) + " has disconnected");
			m_entityHandler.removeEntity(id);
		}



	}
}

void Game::render(Player& player) {

	m_world.render(m_camera);
	m_blockOutline.render(player, m_camera);
	m_particleHandler.render(m_camera);
	m_entityHandler.render(m_camera);
	m_cubeMap.render(m_camera.getProjectionMatrix(), glm::mat4(glm::mat3(m_camera.getViewMatrix())));

}

void Game::destroy() {

	//Freeing world data
	free(m_data);

	m_cubeMap.destroy();
	m_entityHandler.destroy();
	m_world.destroy();
	m_cubeMap.destroy();
	m_particleHandler.destroy();
	m_blockOutline.destroy();
}
