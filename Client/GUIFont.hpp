#pragma once
#include "GUIRenderer.hpp"
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <map>

struct Character {
     unsigned int textureID;
     glm::ivec2   size;
     glm::ivec2   bearing;
     signed long advance;
};

class GUIFont{
public:
     void init(const char* path);

     std::map<char, Character> characters;
};
