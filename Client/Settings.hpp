#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:

     void readFromFile();
     void writeToFile();

     bool showFPS = false;
     bool vsync = false;
     unsigned int front = 0;
     unsigned int back = 0;
     unsigned int up = 0;
     unsigned int down = 0;
     unsigned int left = 0;
     unsigned int right = 0;

     //Runtime Settings(not going to be written to disk)
     float renderDistance = 64.0f;
     float mouseSensibility = 0.3f;
     float playerSpeed = 30.0f;




};

#endif
