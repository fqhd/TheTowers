#pragma once

#include <iostream>
#include <fstream>


class Settings {
public:
    // Functions
    void loadFromFile();
    void writeToFile();

    // Variables
	bool legacyOutline = true;
    bool isVignetteToggled = true;
	bool isDebugToggled = true;
};
