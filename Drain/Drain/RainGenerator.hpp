#pragma once
#include <vector>
#include "Sprite.hpp"

class RainGenerator {
public:
	RainGenerator(int count);
	std::vector<Sprite*> sprites;

};