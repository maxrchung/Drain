#pragma once
#include <vector>
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "Time.hpp"

struct RainDrop {
	Sprite* sprite;
	float startingTime;
	float endingTime;
	float startX;
	float startY;
	float endX;
	float endY;
	float scale;
};

class RainGenerator {
public:
	// Parameters shouldn't be used for RainGenerator, use RainGenerator(); to call function.
	RainGenerator(Time freezeTime,
				  int maxRainCount = 50,
				  int dropCount = 20,  // Bigger the dropCount, faster the initial raindrops fall
				  Time startTime = Time("00:14:00").ms,
				  Time endTime = Time("00:54:00").ms,
				  float acceleration = 1.04f); // Note: should be 1.04 in case I forget

	void VelocityController();
	void RainController();
	void DrawRain(int rainCount);
	std::vector<Sprite*> FreezeRain();
	Vector2 FreezePos();
	float SlowRainBeforeFreeze(float actualDropStart, float actualDropTotalTime);
	void TrackRainDrop(Sprite* sprite, float actualDropStart, float actualDropEnd, float newSize, float spriteEndPosX, float spriteEndPosY);
	float RandomRainVelocity(float minDropTime, float veloDelta);
	float RandomRainTilt(Sprite* sprite);
	Vector2 NewEndCoords(Sprite* sprite, float spriteEndPosX, float spriteEndPosY, float xCoordMax);
	float ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime, float actualDropStart);
	std::vector<Sprite*> sprites;

private:
	const int maxRainCount;
	const int dropCount;
	const Time startTime;
	const Time endTime;
	const float acceleration; // Note: acceleration only supports 0-2

	float minDropTime = 750.0f; // Edit to cap max rain velocity
	const float leftOfScreen;
	float dropTotalTime;
	int totalTime;
	int dropStartTime;
	int dropEndTime;

	const float maxSize = 0.7f; // Used in scaling rain size and determining end y position for rain
	const float rainLength = 102; // because a.png is 102x102

	std::vector<RainDrop> rainDrops;
	std::vector<Sprite*> rainSprites;

	Time freezeTime;
	Time slowPeriod = Time("00:03:00");
	float maxSlow = 2;
};