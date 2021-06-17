#ifndef CONSTANTS_H
#define CONSTANTS_H

// World
const unsigned int CHUNK_WIDTH = 32;
const unsigned int LOCAL_WORLD_WIDTH = 16;
const unsigned int LOCAL_WORLD_HEIGHT = 8;
const unsigned int WORLD_WIDTH = 32;
const unsigned int WORLD_HEIGHT = 8;
constexpr unsigned int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;

// Network
const unsigned int CLIENT_PORT = 7459;
const unsigned int SERVER_PORT = 7456;
const unsigned int PACKET_TRANSMISSION_FREQUENCY = 10;

// Camera
const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 70.0f;
const float SPEED = 25.0f;

// Game
const float ENTITY_MOVEMENT_SHARPNESS = 8.0f;
const unsigned int NUM_PARTICLES = 50;
const float GRAVITY = 12.0f;

// Program
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

#endif