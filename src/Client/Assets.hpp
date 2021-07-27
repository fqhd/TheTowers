#pragma once

#include "Cube.hpp"
#include "Outline.hpp"

class Assets {
public:

	void init();
	const Cube& getCube() const;
	const Outline& getOutline() const;
	void destroy();

private:

	Cube m_cube;
	Outline m_outline;

};