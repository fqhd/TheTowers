#include "WorldData.hpp"

const std::string WORLDDATA_FILE = "world.dat";

WorldData::WorldData() {}

void WorldData::setBlock(uint8_t block, uint x, uint y, uint z) {
	// XXX add safer way to access m_data
	m_data[(y * m_width * m_length) + (z * m_width) + x] = block;
}

void WorldData::loadConfig(const Config& config) {
	m_worldWidth = config.getWorldWidth();
	m_worldLength = config.getWorldLength();
	m_worldHeight = config.getWorldHeight();
	m_chunkWidth = config.getChunkWidth();

	// Allocate memory for the world
	m_data_length = m_worldWidth * m_worldLength * m_worldHeight * m_chunkWidth * m_chunkWidth * m_chunkWidth;
	m_data = static_cast<uint8_t*>(malloc(m_data_length));

	m_width = m_worldWidth * m_chunkWidth;
	m_length = m_worldLength * m_chunkWidth;
	m_height = m_worldHeight * m_chunkWidth;

	// Fill in the memory
	for(unsigned int y = 0; y < m_height; y++){
		for(unsigned int z = 0; z < m_length; z++){
			for(unsigned int x = 0; x < m_width; x++){
				if(y < 20){
					setBlock(5, x, y, z);
				}else if(x == z){
					setBlock(2, x, y, z);
				}else{
					setBlock(0, x, y, z);
				}
			}
		}
	}
}

void WorldData::loadWorldData() {
	std::ifstream file(WORLDDATA_FILE, std::ios::in | std::ios::binary);
	if (!file.good()) {
		std::cerr << "could not open " << WORLDDATA_FILE << " file for reading" << std::endl;
		return;
	}
	for (int i = 0; i < m_data_length; i++) {
		file.read((char*)&m_data[i], sizeof(uint8_t));		
	}
	file.close();
	if(!file.good()) {
      	std::cerr << "Error occurred at reading time!" << std::endl;
      	return;
  	}
}

void WorldData::saveWorldData() {
	std::ofstream file(WORLDDATA_FILE, std::ios::out | std::ios::binary);
	if (!file.good()) {
		std::cerr << "could not open " << WORLDDATA_FILE << " file for writing" << std::endl;
		return;
	}
	for (int i = 0; i < m_data_length; i++) {
		file.write((char*)&m_data[i], sizeof(uint8_t));		
	}
	file.close();
	if(!file.good()) {
      	std::cerr << "Error occurred at writing time!" << std::endl;
		return;
  	}
}

int WorldData::getWidth() { return m_width; }
int WorldData::getHeight() { return m_height; }
int WorldData::getLength() { return m_length; }
uint8_t *WorldData::getDataPtr() { return m_data; }
WorldData::~WorldData() {}