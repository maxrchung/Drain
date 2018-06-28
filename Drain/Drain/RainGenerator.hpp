#pragma once
#include <vector>
#include "Sprite.hpp"
#include "Time.hpp"

class RainGenerator {
public:
	RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, float acceleration = 1.0f);
	float VelocityController(float dropTotalTime, float acceleration);
	std::vector<Sprite*> sprites;

private:
	float minDropTime = 10.0f;
};