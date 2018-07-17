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
	//TODO: Add freeze function and a method to return Sprite*, sprite sizes, and x,y coordinate of sprites currently on screen
	//TODO: Add way to DELETE every raindrop off screen on before startTime and endTime

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
	rainCount *= acceleration; // Increases rain density after every iteration

	DrawRain(rainCount);
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain(int rainCount) {
	static const float topOfScreen = Vector2::ScreenSize.y / 2;
	static const float veloDelta = 10;
	float minDropTime = dropTotalTime / veloDelta;

	for (int i = 0; i < rainCount; i++) {
		// Handle rain positioning
		float rainPosX = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);
		// Handle rain timing
		float actualDropTotalTime = RandomRainVelocity(minDropTime, veloDelta);
		float totalVariance = actualDropTotalTime * 8;
		float dropTimeDelta = RandomRange::calculate(-totalVariance, totalVariance); // This way drop timing of rain will vary based on totalVariance
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

	if (randNum >= 0 && randNum <= 6.5) { // Gets velocity of rain drops based on number randNum which ranges from 1-10
		actualDropTotalTime = RandomRange::calculate(sectionLength * 4, dropTotalTime);
	}
	else if (randNum > 6.5 && randNum <= 8.1) {
		actualDropTotalTime = RandomRange::calculate(sectionLength * 3, sectionLength * 4);
	}
	else if (randNum > 8.1 && randNum <= 9.4) {
		actualDropTotalTime = RandomRange::calculate(sectionLength * 2, sectionLength * 3);
	}
	else if (randNum > 9.4 && randNum <= 9.95) {
		actualDropTotalTime = RandomRange::calculate(sectionLength, sectionLength * 2);
	}
	else if (randNum > 9.95 && randNum <= 10) {
		actualDropTotalTime = RandomRange::calculate(minDropTime, sectionLength);
	}
	
	return actualDropTotalTime;
}

// Randomizes end position of rain to get a rain tilt effect
float RainGenerator::RandomRainTilt(Sprite* sprite) {
	static const float maxTiltVariance = 100;
	int posDelta = RandomRange::calculate(-maxTiltVariance, maxTiltVariance);
	float spritePosX = sprite->position.x + posDelta;
	return spritePosX;
}

// Instantly scales sprite size proportionally to rain velocity upon creation
void RainGenerator::ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime) {
	static const float maxSize = 0.6f;
	static const float minSize = 0.03f;
	float newSize;
	float veloRatio = actualDropTotalTime / dropTotalTime;
	float rainScale = maxSize - veloRatio;

	if (rainScale < 0) { // Ensures newSize isn't a negative number; negative sizes would be fked
		float remainder = -rainScale;
		float minSizeScaler = (1 + remainder) * (1 + remainder);
		newSize = minSize * minSizeScaler;
	}
	else {
		newSize = rainScale * rainScale; // Multiplies scale by itself so rain sprite image scales off total area instead of side length

		if (newSize < minSize) { // So that raindrops that are too small (that aren't even visible in the storyboard) don't exist
			newSize = minSize;
		}
	}

	sprite->Scale(0, 0, 1.0f, newSize);
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