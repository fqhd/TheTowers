#pragma once

#include "Engine/Utils/OutlineRenderer.hpp"
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
	OutlineRenderer m_renderer;
	BlockOutlineShader m_shader;

};
