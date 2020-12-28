#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const unsigned int CHUNK_WIDTH = 32;
const unsigned int CHUNK_SIZE = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;
const unsigned int WORLD_SIZE = 4;
const unsigned int WORLD_HEIGHT = 2;
const float FOV = 90.0f;
const float RATIO = (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT;
const unsigned int PRECISION = 50;
const float DISTANCE = 5.0f;
const float OCCLUSION_FACTOR = 0.8f;
const float GRAVITY = -10.0f;
const float PLAYER_WIDTH = 1.0f;
const float PLAYER_HEIGHT = 2.0f;
const float MENU_WIDTH = 900.0f;
const float MENU_HEIGHT = 600.0f;
const float MENU_BG_WIDTH = MENU_WIDTH + 2.0f;
const float MENU_BG_HEIGHT = MENU_HEIGHT + 2.0f;
const float SLIDER_BUTTON_WIDTH = 8.0f;
const float SLIDER_BUTTON_HEIGHT = 18.0f;
const float MAX_RANGE = 64.0;
const float MAX_SPEED = 50.0f;
const float MAX_FPS = 1000.0f;
const float MAX_SENSIBILITY = 5.0f;
const float MAX_VELOCITY = -12.0f;

#endif
