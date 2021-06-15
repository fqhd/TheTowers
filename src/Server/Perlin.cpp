#include "Perlin.hpp"
#include <random>


void Perlin::createPerlinNoise(int width, int octaves, float bias, float* seed, float *output) {

  srand(time(0)); //Making randomness random every instance

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < width; y++) {
      float fNoise = 0.0f;
      float fScaleAcc = 0.0f;
      float fScale = 1.0f;

      for (int o = 0; o < octaves; o++) {
      int nPitch = width >> o;
      int nSampleX1 = (x / nPitch) * nPitch;
      int nSampleY1 = (y / nPitch) * nPitch;

      int nSampleX2 = (nSampleX1 + nPitch) % width;
      int nSampleY2 = (nSampleY1 + nPitch) % width;

      float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
      float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

      float fSampleT = (1.0f - fBlendX) * seed[nSampleY1 * width + nSampleX1] + fBlendX * seed[nSampleY1 * width + nSampleX2];
      float fSampleB = (1.0f - fBlendX) * seed[nSampleY2 * width + nSampleX1] + fBlendX * seed[nSampleY2 * width + nSampleX2];

      fScaleAcc += fScale;
      fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
      fScale = fScale / bias;
      }

      output[y * width + x] = fNoise / fScaleAcc;
    }
  }

}

void Perlin::init(unsigned int width, unsigned int octaves, float bias){
  m_width = width;
  float* randomNoise = new float[width * width];
  createRandomNoise(randomNoise, width * width);

  m_noise = new float[width * width];
  createPerlinNoise(width, octaves, bias, randomNoise, m_noise);

  delete[] randomNoise;
}

void Perlin::createRandomNoise(float* noise, unsigned int size){
  for(unsigned int i = 0; i < size; i++){
    noise[i] = (rand() % 1000000000) / 1000000000.0f;
  }
}

float Perlin::noise(unsigned int x, unsigned int y){
  return m_noise[m_width * y + x];
}

void Perlin::destroy(){
  delete[] m_noise;
}
