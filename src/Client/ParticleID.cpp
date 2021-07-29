#include "ParticleID.hpp"

ParticleID blockIDtoParticleID(uint8_t _blockID){
	if (_blockID == 1 || _blockID == 2 || _blockID == 3){
		return ParticleID::DIRT;
	}
	return ParticleID::STONE;
}
