#pragma once
#include <cstdint>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float MOUSE_SENSITIVITY = 0.3f;
const int WORLD_WIDTH = 8;
const int WORLD_HEIGHT = 2;
const int WORLD_LENGTH = 4;
const int CHUNK_WIDTH = 32;
const int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;
const int CLIENT_PORT = 7459;
const int SERVER_PORT = 7456;
const int PACKET_TRANSMISSION_FREQUENCY = 10;

enum class GameMsg : uint32_t {
    Server_GetStatus,
    Server_GetPing,

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,

    Game_AddPlayer,
    Game_RemovePlayer,
    Game_UpdatePlayer,
    
};