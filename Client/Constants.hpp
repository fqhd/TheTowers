#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {
public:

     static void loadFromFile();

     static unsigned int getScreenWidth();
     static unsigned int getScreenHeight();
     static unsigned int getChunkWidth();
     static unsigned int getChunkSize();
     static unsigned int getWorldWidth();
     static unsigned int getWorldHeight();
     static float getPlayerReachDistance();
     static float getOcclusionFactor();
     static unsigned int getPrecision();
     static float getMaxPlayerSpeed();
     static float getGravity();
     static unsigned int getMaxRenderDistance();
     static float getMaxMouseSensibility();

private:

     static unsigned int m_screenWidth;
     static unsigned int m_screenHeight;
     static unsigned int m_chunkWidth;
     static unsigned int m_chunkSize;
     static unsigned int m_worldWidth;
     static unsigned int m_worldHeight;
     static float m_playerReachDistance;
     static float m_occlusionFactor;
     static unsigned int m_precision;
     static float m_maxPlayerSpeed;
     static float m_gravity;
     static unsigned int m_maxRenderDistance;
     static float m_maxMouseSensibility;




};

#endif
