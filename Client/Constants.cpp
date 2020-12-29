#include "Constants.hpp"

unsigned int Constants::getScreenWidth() {
     return 1280;
}

unsigned int Constants::getScreenHeight() {
     return 720;
}

float Constants::getGravity() {
     return 12.0f;
}

float Constants::getMaxPlayerSpeed(){
     return 50.0f;
}

unsigned int Constants::getChunkWidth() {
     return 32;
}

float Constants::getMaxMouseSensibility(){
     return 5.0f;
}

unsigned int Constants::getMaxRenderDistance(){
     return 64.0f;
}

unsigned int Constants::getChunkSize() {
     return 32 * 32 * 32;
}

unsigned int Constants::getWorldWidth() {
     return 4;
}

unsigned int Constants::getWorldHeight() {
     return 2;
}

float Constants::getPlayerReachDistance() {
     return 5.0f;
}

float Constants::getOcclusionFactor() {
     return 0.8f;
}

unsigned int Constants::getPrecision(){
     return 50;
}
