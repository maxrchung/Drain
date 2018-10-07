#pragma once
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include <vector>

class Drip {
public:
	static void renderFirstFill();
	static void renderSecondDrips();

private:
	static SpriteCollection buildSpriteCollection(Sprite* const circle, Sprite* const column);
	static SpriteCollection draw(const int startTime, const int endTime, const float centerX, const float columnWidth, const Easing easing);
	static std::vector<float> generatePositions(const int count);

	static constexpr float CIRCLE_FACTOR = 1.5f;
	// Buffer to account for extra spacing on left and right of drips
	static constexpr float COLUMN_WIDTH_BUFFER = 0.94f;
	static const int COLUMN_PIXEL_SIZE = 100;
	static const RandomRange RANDOM_VARIATION;
	static const std::vector<int> FIRST_SPAWN_TIMES;
};