#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int maxRainCount, int dropCount, Time startTime, Time endTime, float acceleration)
	: maxRainCount{ maxRainCount }, dropCount{ dropCount }, startTime{ startTime }, endTime{ endTime }, acceleration{ acceleration },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ endTime.ms - startTime.ms }, rainSpacing{ Vector2::ScreenSize.x / (maxRainCount - 1) } {
	// Note: acceleration only supports 0-2

	//TODO: Cut down SB load 30 to <2 (meme) by removing height and velocity dependence; instead, directly modify totalDropTime (probbly wrong name w/e)
	//TODO: Add freeze function and a method to return Sprite*, sprite sizes, and x,y coordinate of sprites currently on screen
	//IDEA: Every time sprite is created, add it to a sprite vector and once it finishes dropping delete it from the vector
	//IDEA: To freeze drops get the current sprite positions, set their movements to move to their current positions and then create new sprites at their position

	// Initiate drop time values
	dropTotalTime = totalTime / dropCount;
	dropStartTime = startTime.ms;
	dropEndTime = dropStartTime + dropTotalTime;

	while (dropEndTime < endTime.ms) { // Main loop for drawing and animating rain drops
		RainController();
	}

	FreezeRain(freezeTime);
}

// Generates rain sprites and moves them
void RainGenerator::RainController() {
	static int rainCount = maxRainCount; // Rain ended up looking better without a random raincount so rainCount is just maxRainCount
	rainCount *= acceleration; // Increases rain density after every iteration

	DrawRain(rainCount);
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain(int rainCount) {
	static const float xCoordMax = Vector2::ScreenSize.x / 2;
	static const float topOfScreen = Vector2::ScreenSize.y / 2;
	static const float veloDelta = 10;
	float minDropTime = dropTotalTime / veloDelta;

	for (int i = 0; i < rainCount; i++) {
		// Handle rain positioning
		float rainPosX = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);
		static const float rainPosY = topOfScreen + (rainLength / 2);
		// Handle rain timing
		float actualDropTotalTime = RandomRainVelocity(minDropTime, veloDelta);
		float totalVariance = actualDropTotalTime * 8;
		float dropTimeDelta = RandomRange::calculate(-totalVariance, totalVariance); // This way drop timing of rain will vary based on totalVariance
		float actualDropStart = dropStartTime + dropTimeDelta;
		float actualDropEnd = actualDropStart + actualDropTotalTime;

		if (actualDropStart < startTime.ms || actualDropEnd > endTime.ms) { // Ensures drops don't fall outside of time section
			continue;
		}

		// Handle sprite movement
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(rainPosX, rainPosY));
		TrackRainDrop(sprite);

		if (!(freezeTime.ms >= actualDropStart && freezeTime.ms <= actualDropEnd)) { // Removes raindrop sprite from vector if it isn't visible on the screen during freezeTime
			UntrackRainDrop();
		}

		float spriteEndPosX = RandomRainTilt(sprite);
		float spriteEndPosY = -topOfScreen - ((rainLength / 2) * maxSize);

		if (spriteEndPosX > xCoordMax || spriteEndPosX < -xCoordMax) { // Do raindrops fall to the right or left of the screen?
			Coords newCoords = NewEndCoords(sprite, spriteEndPosX, spriteEndPosY, xCoordMax);
			spriteEndPosX = newCoords.x;
			spriteEndPosY = newCoords.y;
		}

		ScaleRainSize(sprite, actualDropTotalTime, minDropTime, actualDropStart);
		sprite->Move(actualDropStart, actualDropEnd, sprite->position, Vector2(spriteEndPosX, spriteEndPosY));
	}
}

void RainGenerator::FreezeRain(Time freezeTime) {
	 //for (int = 0; ) note to self somehow iterate over vector
}

void RainGenerator::TrackRainDrop(Sprite* sprite) {
	rainDrops.push_back(sprite);
}

void RainGenerator::UntrackRainDrop() {
	rainDrops.pop_back();
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
	float spriteEndPosX = sprite->position.x + posDelta;

	return spriteEndPosX;
}

// Adjusts X,Y coords so drops are deleted early in cases where rain drops fall outside of screen due to tilt
struct Coords RainGenerator::NewEndCoords(Sprite* sprite, float spriteEndPosX, float spriteEndPosY, float xCoordMax) {
	float halfDrop = (rainLength / 2) * maxSize;
	float spriteStartX = sprite->position.x;
	float pathLengthY = Vector2::ScreenSize.y + (rainLength / 2);
	float pathLengthX;
	Coords newCoords;

	// Triangle within another similar triangle
	if (spriteEndPosX > xCoordMax) { // Raindrop goes past right of screen
		pathLengthX = spriteEndPosX - spriteStartX;
		float pathLength = sqrt(pow(pathLengthX, 2) + pow(pathLengthY, 2)); // Distance a raindrop travels from start to end

		float xPass = spriteEndPosX - xCoordMax;
		float triangleRatio = xPass / pathLengthX; // Ratio of smaller triangle to bigger triangle
		newCoords.x = spriteEndPosX - xPass + halfDrop;

		float smallPath = pathLength * triangleRatio;
		float yPass = sqrt(pow(smallPath, 2) - pow(xPass, 2));
		newCoords.y = spriteEndPosY + yPass;
	}
	else if (spriteEndPosX < -xCoordMax) { // Raindrop goes past left of screen
		pathLengthX = -(spriteEndPosX - spriteStartX);
		float pathLength = sqrt(pow(pathLengthX, 2) + pow(pathLengthY, 2));

		float xPass = -(spriteEndPosX + xCoordMax);
		float triangleRatio = xPass / pathLengthX;
		newCoords.x = spriteEndPosX + xPass - halfDrop;

		float smallPath = pathLength * triangleRatio;
		float yPass = sqrt(pow(smallPath, 2) - pow(xPass, 2));
		newCoords.y = spriteEndPosY + yPass;
	}

	return newCoords;
}

// Instantly scales sprite size proportionally to rain velocity upon creation
void RainGenerator::ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime, float actualDropStart) {
	static const float minSize = 0.1f;
	float newSize;
	float veloRatio = actualDropTotalTime / dropTotalTime;
	float rainScale = maxSize - veloRatio;

	if (rainScale < 0) { // Ensures newSize isn't a negative number; negative sizes would be fked
		float remainder = -rainScale;
		float minSizeScaler = maxSize - remainder; // Bigger remainder is, bigger veloRatio is, means actualDropTotalTime is bigger (slower velocity). slower the velocity, smaller the raindrops
		newSize = minSize * minSizeScaler;
	}
	else {
		newSize = rainScale * rainScale; // Multiplies scale by itself so rain sprite image scales off total area instead of side length

		if (newSize < minSize) { // So that raindrops that are too small (that aren't even visible in the storyboard) don't exist
			newSize = minSize;
		}
	}

	sprite->Scale(actualDropStart, actualDropStart, 1.0f, newSize);
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