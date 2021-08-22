#include "Converter.hpp"

uint8_t itemIDtoBlockID(ItemID _id){
	return (uint8_t)_id;
}

ParticleID blockIDtoParticleID(uint8_t _blockID){
	return (ParticleID)(_blockID - 1);
}