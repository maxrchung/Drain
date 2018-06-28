#pragma once
#include <vector>
#include "Sprite.hpp"
#include "Time.hpp"

class RainGenerator {
public:
	RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, float acceleration = 1.0f);
	void VelocityController();
	std::vector<Sprite*> sprites;

private:
	const int rainCount;
	const int dropCount;
	const Time startTime;
	const Time endTime;
	const float acceleration;

	float minDropTime = 10.0f;
	const float leftOfScreen;
	float dropTotalTime;
	int totalTime;
	float rainSpacing;
};