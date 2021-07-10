#pragma once

#include <iostream>
#include <fstream>


class Settings {
public:
    // Functions
    void loadFromFile();
    void writeToFile();

    // Variables
    bool isFogToggled = true;
    bool isVignetteToggled = true;
};


