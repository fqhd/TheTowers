#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Config.hpp"

class WorldData {
public:
	WorldData();
	void loadConfig(const Config& config);
	void loadWorldData();
	void saveWorldData();
	void setBlock(uint8_t block, uint x, uint y, uint z);
	int getWidth();
	int getHeight();
	int getLength();
	uint8_t *getDataPtr();
	~WorldData();

private:
	uint8_t *m_data;
	uint data_length;
	uint m_worldWidth;
	uint m_worldLength;
	uint m_worldHeight;
	uint m_chunkWidth;
	int m_width;
	int m_length;
	int m_height;
};