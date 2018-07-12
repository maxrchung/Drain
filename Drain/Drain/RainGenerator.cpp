#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int maxRainCount, int dropCount, Time startTime, Time endTime, float acceleration)
	: maxRainCount{ maxRainCount }, dropCount{ dropCount }, startTime{ startTime }, endTime{ endTime }, acceleration{ acceleration },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ endTime.ms - startTime.ms }, rainSpacing{ Vector2::ScreenSize.x / (maxRainCount - 1) } {
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration, dropcount?
	// acceleration: raindrop accelerates after the current one finishes dropping
	// Note: acceleration only supports 0-2
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Todo: Add relationship between size of rain drop & speed since objects closer (bigger) visually move faster across the screen

	// Initiate drop time values
	dropTotalTime = totalTime / dropCount;
	dropStartTime = startTime.ms;
	dropEndTime = dropStartTime + dropTotalTime;

	while (dropEndTime < endTime.ms) { // Main loop for drawing and animating rain drops
		RainController();
	}
}

// Generates rain sprites and moves them
void RainGenerator::RainController() {
	int rainCount = static_cast<int>(RandomRange::calculate(1, maxRainCount));

	DrawRain(rainCount);
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain(int rainCount) {
	static const float topOfScreen = Vector2::ScreenSize.y / 2;

	for (int i = 0; i < rainCount; i++) {
		float rainPosYDelta = RandomRange::calculate(0, Vector2::ScreenSize.y);
		float rainPosY = topOfScreen + rainPosYDelta;
		float rainPosX = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);

		float dropTimeDelta = RandomRange::calculate(0, dropTotalTime);
		float actualDropStart = dropStartTime + dropTimeDelta;
		float actualDropEnd = dropEndTime + dropTimeDelta;

		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(rainPosX, rainPosY));
		float spritePosX = RandomRainTilt(sprite);
		RandomizeRainSize(sprite);
		sprite->Move(actualDropStart, actualDropEnd, sprite->position, Vector2(spritePosX, -Vector2::ScreenSize.y / 2));
	}
}

// Randomizes end position of rain to get a rain tilt effect
float RainGenerator::RandomRainTilt(Sprite* sprite) {
	float maxTiltVariance = 175;
	int posDelta = RandomRange::calculate(-maxTiltVariance, maxTiltVariance);
	float spritePosX = sprite->position.x + posDelta;
	return spritePosX;
}

// placeholder comment
void RainGenerator::RandomizeRainSize(Sprite* sprite) {
	float minSize = 0.01f;
	float randNum = RandomRange::calculate(minSize * 100.0f, 100.0f);
	float rainScale = randNum / 100.0f;
	sprite->Scale(0, 0, 1.0f, rainScale);
}

// Modifies the velocity of raindrops by changing time a raindrop takes to fall
void RainGenerator::VelocityController() {
	if (dropTotalTime >= minDropTime) { // Ensures rain doesn't fall faster than minDropTime
		dropTotalTime *= (2.0f - acceleration);
	}

	// Increments time after row of rain is finished falling
	dropStartTime += dropTotalTime;
	dropEndTime = dropStartTime + dropTotalTime;
}