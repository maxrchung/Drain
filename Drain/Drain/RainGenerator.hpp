#pragma once
#include <vector>
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "Time.hpp"

class RainGenerator {
public:
	// Parameters shouldn't be used for RainGenerator, use RainGenerator(); to call function.
	RainGenerator(int maxRainCount = 500,
				  int dropCount = 8,  // Bigger the dropCount, faster the initial raindrops fall
				  Time startTime = Time("00:05:584").ms,
				  Time endTime = Time("00:54:00").ms,
				  float acceleration = 1.08f);

	void VelocityController();
	void RainController();
	void DrawRain(int rainCount);
	float RandomRainVelocity(float maxVeloVariance);
	float RandomRainTilt(Sprite* sprite);
	void RandomizeRainSize(Sprite* sprite, float rainPosYDelta, float maxVeloVariance);
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
	float rainSpacing;
	int dropStartTime;
	int dropEndTime;
};