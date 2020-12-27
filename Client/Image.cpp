#include "Image.hpp"
#include "Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void Image::loadFromFile(const std::string& path, int desiredChannels){
     m_imageData = stbi_load(path.c_str(), &m_width, &m_height, &m_numChannels, desiredChannels);
     if(!m_imageData){
          Utils::log("Image: Failed to load image: " + path);
          return;
     }
}

Pixel Image::getPixel(unsigned int x, unsigned int y){
     //Range check
     if(x > m_width || y > m_height || x < 0 || y < 0) return Pixel();
     Pixel p;
     p.r = m_imageData[y * m_numChannels * m_width + x * m_numChannels];
     p.g = m_imageData[y * m_numChannels * m_width + x * m_numChannels + 1];
     p.b = m_imageData[y * m_numChannels * m_width + x * m_numChannels + 2];
     p.a = m_imageData[y * m_numChannels * m_width + x * m_numChannels + 3];
     return p;
}

int Image::getWidth(){
     return m_width;
}

int Image::getHeight(){
     return m_height;
}

int Image::getNumChannels(){
     return m_numChannels;
}


unsigned char* Image::getData(){
     return m_imageData;
}

void Image::free(){
     stbi_image_free(m_imageData);
}
