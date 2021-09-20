#pragma once

#include "Cube.hpp"
#include "Shader.hpp"
#include "Player.hpp"
#include "Assets.hpp"
#include "LegacyOutline.hpp"

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

	// Private Utility Functions
	Face getFace(VisibleBlocks& visibleBlocks);

	// Class objects
	LegacyOutline m_legacyOutline;
	Assets* m_assets = nullptr;
	Shader m_shader;

};
