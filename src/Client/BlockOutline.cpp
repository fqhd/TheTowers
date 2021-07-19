#include "BlockOutline.hpp"

void BlockOutline::init(){
	m_shader.init();
	m_renderer.init();
}

void BlockOutline::render(Player* player, Camera& camera){
	//Checking if the player is facing a block in order to draw an outline
	if(!player->visibleBlocks.lookingAtBlock || player->visibleBlocks.isInsideBlock) return;

	//Getting the face of the block that the player is facing
	Face blockFace = getFace(player->visibleBlocks);

	//Binding the shader, loading a couple uniforms and rendering a face based on the position of the block
	m_shader.bind();
	m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_shader.loadViewMatrix(camera.getViewMatrix());
	m_shader.loadBlockPosition(player->visibleBlocks.breakableBlock); //We send the position of the block to the vertex shader which will get added to the vertices and form a face

	m_renderer.renderFace(blockFace); //This functions only renders a 1 of the 6 faces of a cube based on the parameter given

	m_shader.unbind();
}

Face BlockOutline::getFace(VisibleBlocks& visibleBlocks){
	math::ivec3 deltaBlockFace = visibleBlocks.placeableBlock - visibleBlocks.breakableBlock;

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
	m_shader.destroy();
	m_renderer.destroy();
}
