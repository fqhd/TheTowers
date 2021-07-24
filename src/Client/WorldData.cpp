#include "WorldData.hpp"


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
	data_length = m_worldWidth * m_worldLength * m_worldHeight * m_chunkWidth * m_chunkWidth * m_chunkWidth;
	m_data = static_cast<uint8_t*>(malloc(data_length));

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

void WorldData::loadWorldData(){}

void WorldData::saveWorldData() {}

int WorldData::getWidth() { return m_width; }
int WorldData::getHeight() { return m_height; }
int WorldData::getLength() { return m_length; }
uint8_t *WorldData::getDataPtr() { return m_data; }
WorldData::~WorldData() {}