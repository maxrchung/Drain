#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int maxRainCount, int dropCount, Time startTime, Time endTime, float acceleration)
	: maxRainCount{ maxRainCount }, dropCount{ dropCount }, startTime{ startTime }, endTime{ endTime }, acceleration{ acceleration },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ endTime.ms - startTime.ms }, rainSpacing{ Vector2::ScreenSize.x / (maxRainCount - 1) } {
	// Note: acceleration only supports 0-2

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
	// int rainCount = static_cast<int>(RandomRange::calculate(maxRainCount, maxRainCount)); 
	static int rainCount = maxRainCount; // Rain ended up looking better without a random raincount so rainCount is just maxRainCount
	rainCount += 10;

	DrawRain(rainCount);
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain(int rainCount) {
	static const float topOfScreen = Vector2::ScreenSize.y / 2;
	static const float maxVeloVariance = Vector2::ScreenSize.y * 30; // Higher a raindrop starts, faster it needs to get from top to bottom of screen

	for (int i = 0; i < rainCount; i++) {
		float rainPosYDelta = RandomRainVelocity(maxVeloVariance);
		float rainPosY = topOfScreen + rainPosYDelta;
		float rainPosX = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);

		float dropTimeDelta = RandomRange::calculate(0, dropTotalTime);
		float actualDropStart = dropStartTime + dropTimeDelta;
		float actualDropEnd = dropEndTime + dropTimeDelta;

		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(rainPosX, rainPosY));
		float spritePosX = RandomRainTilt(sprite);
		RandomizeRainSize(sprite, rainPosYDelta, maxVeloVariance);
		sprite->Move(actualDropStart, actualDropEnd, sprite->position, Vector2(spritePosX, -Vector2::ScreenSize.y / 2));
	}
}

// Returns a random number to increase rainPosY which visually increases rain velocity. Smaller rain sizes (slower velocity) are made more probable for visual effect
float RainGenerator::RandomRainVelocity(float maxVeloVariance) {
	float rainPosYDelta;
	float randNum = RandomRange::calculate(0, 10);
	// Each case has a 85%, 13.5%, and 1.5% probability respectively
	if (randNum >= 0 && randNum <= 8.5) {
		rainPosYDelta = RandomRange::calculate(0.01f, maxVeloVariance / 3);
	}
	else if (randNum > 8.5 && randNum <= 9.85) {
		rainPosYDelta = RandomRange::calculate(maxVeloVariance / 3, (maxVeloVariance / 3) * 2);
	}
	else if (randNum > 9.85 && randNum <= 10) {
		rainPosYDelta = RandomRange::calculate((maxVeloVariance / 3) * 2, maxVeloVariance);
	}
	
	return rainPosYDelta;
}

// Randomizes end position of rain to get a rain tilt effect
float RainGenerator::RandomRainTilt(Sprite* sprite) {
	float maxTiltVariance = 450;
	int posDelta = RandomRange::calculate(-maxTiltVariance, maxTiltVariance);
	float spritePosX = sprite->position.x + posDelta;
	return spritePosX;
}

// Instantly scales sprite size proportionally to rain velocity upon creation
void RainGenerator::RandomizeRainSize(Sprite* sprite, float rainPosYDelta, float maxVeloVariance) {
	float rainScale = rainPosYDelta / maxVeloVariance;
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