#include "BlockOutline.hpp"

void BlockOutline::init(){
	m_outline.init();
	m_shader.load("block_outline");
	m_legacyOutline.init();
}

void BlockOutline::render(Player* player, Camera& camera, bool _legacyOutline){
	//Checking if the player is facing a block in order to draw an outline
	if(!player->visibleBlocks.lookingAtBlock) return;

	//Getting the face of the block that the player is facing
	Face blockFace;
	if(!_legacyOutline) blockFace = getFace(player->visibleBlocks);

	//Binding the shader, loading a couple uniforms and rendering a face based on the position of the block
	m_shader.bind();
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("view", camera.getViewMatrix());
	glm::ivec3 bb = player->visibleBlocks.breakableBlock; // Getting the breakable block
	glm::vec3 float_bb(bb.x, bb.y, bb.z); // Calculating the floating point version of the breakable block
	m_shader.loadUniform("blockPosition", float_bb); // We send the position of the block to the vertex shader which will get added to the vertices and form a face
	m_shader.loadUniform("legacyOutline", _legacyOutline);
	if(_legacyOutline){
		m_legacyOutline.render();
	}else{
		m_outline.render(blockFace, 1);
	}


	m_shader.unbind();
}

Face BlockOutline::getFace(VisibleBlocks& visibleBlocks){
	glm::ivec3 deltaBlockFace = visibleBlocks.placeableBlock - visibleBlocks.breakableBlock;

	if(deltaBlockFace.x == 1){
		return FACE_4;
	} else if(deltaBlockFace.x == -1){
		return FACE_3;
	}else if(deltaBlockFace.z == 1){
		return FACE_2;
	} else if(deltaBlockFace.z == -1){
		return FACE_0;
	}else if(deltaBlockFace.y == 1){
		return FACE_1;
	} else if(deltaBlockFace.y == -1){
		return FACE_5;
	}

	return FACE_0;
}

void BlockOutline::destroy(){
	m_legacyOutline.destroy();
	m_outline.destroy();
	m_shader.destroy();
}
