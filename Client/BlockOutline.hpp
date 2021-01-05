#ifndef BLOCK_OUTLINE_H
#define BLOCK_OUTLINE_H

#include "OutlineRenderer.hpp"
#include "BlockOutlineShader.hpp"
#include "Player.hpp"
#include "Transform.hpp"



class BlockOutline {
public:

     void init();
     void render(Player& player, Camera& camera);
     void destroy();

private:

     //Private Utility Functions
     Face getFace(const glm::vec3& toCameraVector);

     //Class objects
     OutlineRenderer m_renderer;
     BlockOutlineShader m_shader;
     Transform m_transform;

};

#endif
