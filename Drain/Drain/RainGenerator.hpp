#pragma once
#include <vector>
#include "Sprite.hpp"
#include "Time.hpp"

class RainGenerator {
public:
	RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, bool acceleration = false);
	std::vector<Sprite*> sprites;

};