#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {
public:

  static void loadFromFile();
  static void printDebugMessage();

  static unsigned int getScreenWidth();
  static unsigned int getScreenHeight();
  static unsigned int getChunkWidth();
  static unsigned int getChunkSize();
  static unsigned int getLocalWorldWidth();
  static unsigned int getWorldWidth();
  static unsigned int getWorldHeight();
  static unsigned int getNumParticles();
  static float getPlayerReachDistance();
  static float getOcclusionFactor();
  static unsigned int getPrecision();
  static float getMaxPlayerSpeed();
  static float getGravity();
  static unsigned int getMaxRenderDistance();
  static float getMaxMouseSensibility();
  static float getMaxGradient();
  static float getMaxDensity();
  static float getEntityMovementSharpness();
	static unsigned short getClientPort();
	static unsigned short getServerPort();
	static unsigned int getPacketTransmissionFrequency();

private:

  static unsigned int m_screenWidth;
  static unsigned int m_screenHeight;
  static unsigned int m_chunkWidth;
  static unsigned int m_localWorldWidth;
  static unsigned int m_worldWidth;
  static unsigned int m_worldHeight;
  static unsigned int m_numParticles;
  static float m_playerReachDistance;
  static float m_occlusionFactor;
  static unsigned int m_precision;
  static float m_maxPlayerSpeed;
  static float m_gravity;
  static unsigned int m_maxRenderDistance;
  static float m_maxMouseSensibility;
  static float m_maxGradient;
  static float m_maxDensity;
  static float m_entityMovementSharpness;
	static unsigned short m_clientPort;
	static unsigned short m_serverPort;
	static unsigned int m_packetTransmissionFrequency;




};

#endif
