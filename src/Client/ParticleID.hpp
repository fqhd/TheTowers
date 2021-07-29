#pragma once

#include <cstdint>

// THE ORDER IN WHICH THE PARTICLES ARE DEFINED MUST MATCH THE ORDER IN WHICH THEY ARE ASSIGNED IN ParticleTexture.cpp:populateUVQuadArray().
enum class ParticleID : unsigned int {
	DIRT,
	STONE
};

ParticleID blockIDtoParticleID(uint8_t _blockID);