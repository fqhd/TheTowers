#pragma once

#include "Cube.hpp"
#include "Outline.hpp"
#include "Model.hpp"

class Assets {
public:

	void init();
	const Cube& getCube() const;
	const Outline& getOutline() const;
	const Model& getModel() const;
	void destroy();

private:

	Cube m_cube;
	Outline m_outline;
	Model m_entityModel;

};