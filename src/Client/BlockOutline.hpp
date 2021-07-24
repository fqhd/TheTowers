#pragma once

#include "Engine/Utils/Cube.hpp"
#include "Engine/Utils/BlockOutlineShader.hpp"
#include "Player.hpp"

class BlockOutline {
public:

	void init();
	void render(Player* player, Camera& camera);
	void destroy();

private:

	//Private Utility Functions
	Face getFace(VisibleBlocks& visibleBlocks);

	//Class objects
	Cube m_cube;
	BlockOutlineShader m_shader;

};
