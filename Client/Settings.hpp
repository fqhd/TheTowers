#ifndef SETTINGS_H
#define SETTINGS_H


struct Settings {

     bool showFPS = false;
     bool vsync = false;
     float maxFps = 0.02f;
     float playerSpeed = 5.0f;
     float mouseSensibility = 0.3f;
     unsigned int front = 0;
     unsigned int back = 0;
     unsigned int up = 0;
     unsigned int down = 0;
     unsigned int left = 0;
     unsigned int right = 0;
     float range = 0.5f;

};

#endif
