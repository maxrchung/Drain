#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(Time startTime, Time endTime, bool willFreeze, float acceleration, Time freezeTime, int dropCount)
	: startTime{ startTime }, endTime{ endTime }, willFreeze{ willFreeze }, acceleration{ acceleration }, freezeTime {freezeTime}, dropCount{ dropCount },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ static_cast<float>(endTime.ms - startTime.ms) } {

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
	rainCount *= acceleration; // Increases rain density after every iteration

	DrawRain();
	VelocityController();
}

// Creates amount of raindrops in a row, rainCount, and drops it down the screen
void RainGenerator::DrawRain() {
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
		bool freezeFlag = false;
		float actualDropEnd = SlowRainBeforeFreeze(actualDropStart, actualDropTotalTime, freezeFlag);

		if (actualDropStart < startTime.ms || actualDropStart > freezeTime.ms || (!willFreeze && actualDropStart > endTime.ms)) { // Ensures drops don't fall outside of time section & freezeTime
			continue;
		}

		// Handle sprite movement
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(rainPosX, rainPosY));

		float spriteEndPosX = RandomRainTilt(sprite);
		float spriteEndPosY = -topOfScreen - ((rainLength / 2) * maxSize);

		if (spriteEndPosX > xCoordMax || spriteEndPosX < -xCoordMax) { // Do raindrops fall to the right or left of the screen?
			Vector2 newCoords = NewEndCoords(sprite, spriteEndPosX, spriteEndPosY, xCoordMax);
			spriteEndPosX = newCoords.x;
			spriteEndPosY = newCoords.y;
		}

		float rainSize = ScaleRainSize(sprite, actualDropTotalTime, minDropTime, actualDropStart);
		TrackAllRainDrops(sprite);

		ColorRain(sprite, actualDropStart, actualDropEnd);

		if (willFreeze && (freezeTime.ms >= actualDropStart && freezeTime.ms <= actualDropEnd)) { // Tracks raindrop sprite from vector if drop is visible on the screen during freezeTime
			TrackRainDrop(sprite, actualDropStart, actualDropEnd, rainSize, spriteEndPosX, spriteEndPosY);
			Vector2 freezePos = FreezePos();
			sprite->Move(actualDropStart, freezeTime.ms, sprite->position, Vector2(freezePos.x, freezePos.y));
		}
		else { // If this particular raindrop isn't being frozen, drop it to the bottom of the screen
			auto easing = Easing::Linear;
			if (freezeFlag) {
				easing = Easing::QuadOut;
			}
			sprite->Move(actualDropStart, actualDropEnd, sprite->position, Vector2(spriteEndPosX, spriteEndPosY), easing);
		}
	}
}

// Gets the appropriate x and y positions for a raindrop that will be frozen
Vector2 RainGenerator::FreezePos() {
	Vector2 freezePos;
	RainDrop rainDrop = rainDrops.back(); // Gets the newest added rainDrop which is added by TrackRainDrop

	float totalTime = rainDrop.endingTime - rainDrop.startingTime;
	float untilFreeze = freezeTime.ms - rainDrop.startingTime;
	float ratio = untilFreeze / totalTime;
	float xDiff = rainDrop.endX - rainDrop.startX;
	float yDiff = rainDrop.endY - rainDrop.startY;

	float freezeDiffX = xDiff * ratio;
	float freezeDiffY = yDiff * ratio;

	// Directly replace the end positions in the sprite class with the X, Y coordinates of the rain in frozen state
	freezePos.x = rainDrop.startX + freezeDiffX;
	freezePos.y = rainDrop.startY + freezeDiffY;

	rainSprites.push_back(rainDrop.sprite); // Save the sprite to a sprite vector which is used by walker boi

	return freezePos;
}

// Returns a vector of structures containing rain information at a certain time (doesn't actually freeze rain lol)
std::vector<Sprite*> RainGenerator::FreezeRain() {
	return rainSprites;
}

float RainGenerator::SlowRainBeforeFreeze(float actualDropStart, float actualDropTotalTime, bool& freezeFlag) {
	float slowStartTime = freezeTime.ms - slowPeriod.ms;
	float timeFromStartSlow = actualDropStart - slowStartTime;
	float slowRatio = timeFromStartSlow / slowPeriod.ms;

	if (actualDropStart >= slowStartTime) { // Slows down drops a certain time before freezeTime
		float realActualDropTotalTime = actualDropTotalTime + (actualDropTotalTime * (maxSlow * slowRatio));
		float actualDropEnd = actualDropStart + realActualDropTotalTime;
		freezeFlag = true;
		return actualDropEnd;
	}
	else { // Won't increase actualDropEnd until it's time to slow down rain drops
		return actualDropStart + actualDropTotalTime;
	}
}

// Adds raindrop information in a struct into a struct vector
void RainGenerator::TrackRainDrop(Sprite* sprite, float actualDropStart, float actualDropEnd, float rainSize, float spriteEndPosX, float spriteEndPosY) {
	RainDrop rainDrop;
	rainDrop.startingTime = actualDropStart;
	rainDrop.endingTime = actualDropEnd;
	rainDrop.scale = rainSize;
	rainDrop.sprite = sprite;
	rainDrop.startX = sprite->position.x;
	rainDrop.startY = sprite->position.y;
	rainDrop.endX = spriteEndPosX;
	rainDrop.endY = spriteEndPosY;

	rainDrops.push_back(rainDrop);
}

void RainGenerator::TrackAllRainDrops(Sprite* sprite) {
	sprites.push_back(sprite);
}

// Returns the actual total time(ms) it takes for a drop to fall across the screen.. Smaller rain sizes (slower velocity) are made more probable for visual effect
float RainGenerator::RandomRainVelocity(float minDropTime, float veloDelta) {
	float actualDropTotalTime;
	static const float sections = 5; // How many different "sections" of velocity are to be sorted by probability
	float sectionLength = dropTotalTime / sections;
	float randNum = RandomRange::calculate(0, 1000, 100);

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
Vector2 RainGenerator::NewEndCoords(Sprite* sprite, float spriteEndPosX, float spriteEndPosY, float xCoordMax) {
	float halfDrop = (rainLength / 2) * maxSize;
	float spriteStartX = sprite->position.x;
	float pathLengthY = Vector2::ScreenSize.y + (rainLength / 2);
	float pathLengthX;
	Vector2 newCoords;

	// Triangle within another similar triangle
	if (spriteEndPosX > xCoordMax) { // Raindrop goes past right of screen
		pathLengthX = spriteEndPosX - spriteStartX;
		float pathLength = sqrt(pow(pathLengthX, 2) + pow(pathLengthY, 2)); // Distance a raindrop travels from start to end (pythagorean meme)

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
float RainGenerator::ScaleRainSize(Sprite* sprite, float actualDropTotalTime, float minDropTime, float actualDropStart) {
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

	sprite->Scale(actualDropStart, actualDropStart, newSize, newSize);

	return newSize;
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

void RainGenerator::ColorRain(Sprite * sprite, float startTime, float endTime) {
	Swatch::colorFgToFgSprites({ sprite }, startTime, endTime);
}