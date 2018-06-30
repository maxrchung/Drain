#pragma once
#include <vector>
#include "Sprite.hpp"
#include "Time.hpp"

class RainGenerator {
public:
	//Parameters shouldn't be used for RainGenerator, use RainGenerator(); to call function.
	RainGenerator(int rainCount = 5,
				  int dropCount = 10, 
				  Time startTime = Time("00:14:00").ms, 
				  Time endTime = Time("00:54:00").ms,
		          float acceleration = 1.2f);

	void VelocityController();
	void DrawRain();
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
	int dropStartTime;
	int dropEndTime;
};