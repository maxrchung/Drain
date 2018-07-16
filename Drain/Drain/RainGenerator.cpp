#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int maxRainCount, int dropCount, Time startTime, Time endTime, float acceleration)
	: maxRainCount{ maxRainCount }, dropCount{ dropCount }, startTime{ startTime }, endTime{ endTime }, acceleration{ acceleration },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ endTime.ms - startTime.ms }, rainSpacing{ Vector2::ScreenSize.x / (maxRainCount - 1) } {
	// Note: acceleration only supports 0-2

	//TODO: Cut down SB load 30 to <2 (meme) by removing height and velocity dependence; instead, directly modify totalDropTime (probbly wrong name w/e)
	//FIX: All sprites are spawned at the top on instantiation, should only be spawned when needed
	//FIX: Perspective & speed, sporadic rain
	//TODO: Add freeze function and a method to return Sprite*, sprite sizes, and x,y coordinate of sprites currently on screen

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
	rainCount += 10; // Increases rain density after every iteration

	DrawRain(rainCount);
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain(int rainCount) {
	static const float topOfScreen = Vector2::ScreenSize.y / 2;
	//static const float maxVeloVariance = Vector2::ScreenSize.y * 30; // Higher a raindrop starts, faster it needs to get from top to bottom of screen
	static const float veloDelta = 30;
	float minDropTime = dropTotalTime / veloDelta;

	for (int i = 0; i < rainCount; i++) {
		// Handle rain positioning
		float rainPosX = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);
		// Handle rain timing
		float actualDropTotalTime = RandomRainVelocity(minDropTime, veloDelta);
		float dropTimeDelta = RandomRange::calculate(0, actualDropTotalTime);
		float actualDropStart = dropStartTime + dropTimeDelta;
		float actualDropEnd = actualDropStart + actualDropTotalTime;
		// Handle sprite movement
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(rainPosX, topOfScreen));
		float spritePosX = RandomRainTilt(sprite);
		ScaleRainSize(sprite, actualDropTotalTime, minDropTime);
		sprite->Move(actualDropStart, actualDropEnd, sprite->position, Vector2(spritePosX, -Vector2::ScreenSize.y / 2));
	}
}

// Returns the actual total time(ms) it takes for a drop to fall across the screen.. Smaller rain sizes (slower velocity) are made more probable for visual effect
float RainGenerator::RandomRainVelocity(float minDropTime, float veloDelta) {
	float actualDropTotalTime;
	static const float sections = 5; // How many different "sections" of velocity are to be sorted by probability
	float sectionLength = dropTotalTime / sections;
	float randNum = RandomRange::calculate(0, 10);

	// Each case has a 85%, 13.5%, and 1.5% probability respectively
	if (randNum >= 0 && randNum <= 7) {
		actualDropTotalTime = RandomRange::calculate(sectionLength * 4, dropTotalTime);
	}
	else if (randNum > 7 && randNum <= 8.5) {
		actualDropTotalTime = RandomRange::calculate(sectionLength * 3, sectionLength * 4);
	}
	else if (randNum > 8.5 && randNum <= 9.5) {
		actualDropTotalTime = RandomRange::calculate(sectionLength * 2, sectionLength * 3);
	}
	else if (randNum > 9.5 && randNum <= 9.85) {
		actualDropTotalTime = RandomRange::calculate(sectionLength, sectionLength * 2);
	}
	else if (randNum > 9.85 && randNum <= 10) {
		actualDropTotalTime = RandomRange::calculate(minDropTime, sectionLength);
	}
	
	return actualDropTotalTime;
}

// Randomizes end position of rain to get a rain tilt effect
float RainGenerator::RandomRainTilt(Sprite* sprite) {
	static const float maxTiltVariance = 100;
	static const int posDelta = RandomRange::calculate(-maxTiltVariance, maxTiltVariance);
	float spritePosX = sprite->position.x + posDelta;
	return spritePosX;
}

// Instantly scales sprite size proportionally to rain velocity upon creation
void RainGenerator::ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime) {
	static const float maxScale = 1.0f;
	float rainScale = 1 - (actualDropTotalTime / dropTotalTime);
	sprite->Scale(0, 0, maxScale, rainScale);
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