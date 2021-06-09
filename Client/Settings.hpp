#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:

	Settings();

	void readFromFile();
	void writeToFile();

	bool showFPS = false;
	bool vsync = false;
	bool showDebugInfo = false;
	unsigned int front = 0;
	unsigned int back = 0;
	unsigned int up = 0;
	unsigned int down = 0;
	unsigned int left = 0;
	unsigned int right = 0;

	//Runtime Settings(not going to be written to disk)
	float mouseSensibility = 0.0f;
	float playerSpeed = 0.0f;
	float gradient = 0.0f;
	float density = 0.0f;

};

#endif
