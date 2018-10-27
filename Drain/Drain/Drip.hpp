#pragma once
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include <vector>

class Drip {
public:
	// Returns SpriteCollection for drip with specified parameters
	// spawnTime: When to create the drip
	// center: Center of the drip dot
	// columnWidth: How wide to scale the column, note that this is not exact due to anti-aliased borders and added buffer space
	static SpriteCollection makeWalkerDrip(const Time& spawnTime, const Vector2& center, const float columnWidth);
	static void renderBackground();
	static void renderFirstFill();
	static std::vector<SpriteCollection> renderSecondDrips();

private:
	static SpriteCollection buildSpriteCollection(Sprite* const circle, Sprite* const column);
	static SpriteCollection draw(const int startTime, const int endTime, const float left, const float right, const bool drawPartial = false);
	static std::vector<float> generatePositions(const int count);

	static constexpr float CIRCLE_FACTOR = 1.5f;
	// Buffer to account for extra spacing on left and right of drips
	static constexpr float COLUMN_WIDTH_BUFFER = 0.92f;
	static const int COLUMN_PIXEL_SIZE = 100;
	static const RandomRange PARTIAL_DRAW_RANDOM;
	static const RandomRange RANDOM_VARIATION;
	static const std::vector<int> BACKGROUND_SPAWN_TIMES;
	static const std::vector<int> FIRST_SPAWN_TIMES;
	static const std::vector<int> SECOND_SPAWN_TIMES;
};