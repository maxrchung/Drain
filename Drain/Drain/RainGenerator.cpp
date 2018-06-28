#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, float acceleration) {
	//Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration, dropcount?
	//acceleration: raindrop accelerates after the current one finishes dropping
	//Note: acceleration only supports 0-2

	int leftOfScreen = -Vector2::ScreenSize.x / 2;
	int rainSpacing = Vector2::ScreenSize.x / (rainCount-1);
	int totalTime = endTime.ms - startTime.ms;
	int dropTotalTime = totalTime / dropCount;

	int dropStartTime = startTime.ms;
	int dropEndTime = dropStartTime + dropTotalTime;

	while (dropEndTime < endTime.ms) {
		for (int i = 0; i < rainCount; i++) {
			Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(leftOfScreen + i * rainSpacing, Vector2::ScreenSize.y / 2));
			sprite->Move(dropStartTime, dropEndTime, sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
		}

		dropTotalTime = VelocityController(dropTotalTime, acceleration);

		dropStartTime += dropTotalTime;
		dropEndTime = dropStartTime + dropTotalTime;
	}
}

//Modifies the velocity of raindrops by changing time a raindrop takes to fall
float RainGenerator::VelocityController(float dropTotalTime, float acceleration) {
	if (dropTotalTime >= minDropTime) { //Ensures rain doesn't fall faster than minDropTime
		return dropTotalTime * (2.0f - acceleration);
	}
	return dropTotalTime;
}

