#include "BlockOutline.hpp"

void BlockOutline::init(){
     m_shader.init();
     m_renderer.init();
     m_transform.init(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
}

void BlockOutline::render(Player& player, Camera& camera){

     if(!player.visibleBlocks.lookingAtBlock) return;

     //Calculate transform based on player viewable block
     m_transform.setPosition(player.visibleBlocks.breakableBlock);

     glm::vec3 blockPos = glm::vec3(player.visibleBlocks.breakableBlock.x, player.visibleBlocks.breakableBlock.y, player.visibleBlocks.breakableBlock.z);
     glm::vec3 blockCenter = blockPos + glm::vec3(0.5f, 0.5f, 0.5f);

     Face f = getFace(camera.getPosition() - blockCenter);

     m_shader.bind();
     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadModelMatrix(m_transform.getMatrix());

     m_renderer.renderFace(f);

     m_shader.unbind();

}

Face BlockOutline::getFace(const glm::vec3& toCameraVector){
     float x = toCameraVector.x;
     float y = toCameraVector.y;
     float z = toCameraVector.z;

     return (Face)((FACE_0 + (x > 0)) * (fabs(x) > fabs(y) && fabs(x) > fabs(z)) + (FACE_2 + (y > 0)) * (fabs(y) > fabs(x) && fabs(y) > fabs(z)) + (FACE_4 + (z > 0)) * (fabs(z) > fabs(x) && fabs(z) > fabs(y)));

}

void BlockOutline::destroy(){
     m_shader.destroy();
     m_renderer.destroy();
}
