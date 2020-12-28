#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
     bool showFPS = false;
     bool vsync = false;
     unsigned int maxFps = 60;
     unsigned int playerSpeed = 20;
     unsigned int mouseSensibility = 30;
     unsigned int front = 0;
     unsigned int back = 0;
     unsigned int up = 0;
     unsigned int down = 0;
     unsigned int left = 0;
     unsigned int right = 0;
     float range = 0.0f;

};

#endif
