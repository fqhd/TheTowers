#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>


class Settings {
public:
    // Functions
    void loadFromFile();
    void writeToFile();

    // Variables
    bool isFogToggled = true;
};

#endif
