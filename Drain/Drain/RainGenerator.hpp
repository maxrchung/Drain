#pragma once
#include <vector>
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "Time.hpp"

struct Coords {
	float x;
	float y;
};

class RainGenerator {
public:
	// Parameters shouldn't be used for RainGenerator, use RainGenerator(); to call function.
	RainGenerator(int maxRainCount = 50,
				  int dropCount = 20,  // Bigger the dropCount, faster the initial raindrops fall
				  Time startTime = Time("00:14:00").ms,
				  Time endTime = Time("00:54:00").ms,
				  float acceleration = 1.04f); // Note: should be 1.04 in case I forget

	void VelocityController();
	void RainController();
	void DrawRain(int rainCount);
	void FreezeRain(Time freezeTime);
	void TrackRainDrop(Sprite* sprite);
	void UntrackRainDrop();
	float RandomRainVelocity(float minDropTime, float veloDelta);
	float RandomRainTilt(Sprite* sprite);
	struct Coords NewEndCoords(Sprite* sprite, float spriteEndPosX, float spriteEndPosY, float xCoordMax);
	void ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime, float actualDropStart);
	std::vector<Sprite*> sprites;

private:
	const int maxRainCount;
	const int dropCount;
	const Time startTime;
	const Time endTime;
	const float acceleration;

	float minDropTime = 20.0f;
	const float leftOfScreen;
	float dropTotalTime;
	int totalTime;
	float rainSpacing; // Probably dont need this
	int dropStartTime;
	int dropEndTime;

	const float maxSize = 0.6f; // Used in scaling rain size and determining end y position for rain
	const float rainLength = 102; // because a.png is 102x102

	std::vector<Sprite*> rainDrops;
	Time freezeTime = Time("00:53:00").ms;
};