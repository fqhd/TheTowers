#pragma once

#include "Engine/Utils/Cube.hpp"
#include "Engine/Utils/BlockOutlineShader.hpp"
#include "Player.hpp"
#include "Assets.hpp"

enum Face {
	FACE_0,
	FACE_1,
	FACE_2,
	FACE_3,
	FACE_4,
	FACE_5,
};

class BlockOutline {
public:

	void init(Assets* _assets);
	void render(Player* player, Camera& camera);
	void destroy();

private:

	//Private Utility Functions
	Face getFace(VisibleBlocks& visibleBlocks);

	//Class objects
	Assets* m_assets = nullptr;
	BlockOutlineShader m_shader;

};
