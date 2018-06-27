#pragma once
#include <vector>
#include "Sprite.hpp"

class RainGenerator {
public:
	RainGenerator(int rainCount);
	std::vector<Sprite*> sprites;

};