#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, bool acceleration) {
	//Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration, dropcount?
	//acceleration: raindrop accelerates after the current one finishes dropping
	//Note: acceleration is fixed at 1.1f because any other number is fked

	float acceler8 = 1.0f;

	if (acceleration) {
		acceler8 = 1.1f;
	}

	int leftOfScreen = -Vector2::ScreenSize.x / 2;
	int rainSpacing = Vector2::ScreenSize.x / (rainCount-1);
	int totalTime = endTime.ms - startTime.ms;
	int dropTotalTime = totalTime / dropCount;

	int actualDropCount = round(dropCount * pow(acceler8, dropCount));

	int dropStartTime = startTime.ms;
	int dropEndTime = dropStartTime + dropTotalTime;

	for (int rainRow = 0; rainRow < actualDropCount; rainRow++) {
		for (int i = 0; i < rainCount; i++) {
			Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(leftOfScreen + i * rainSpacing, Vector2::ScreenSize.y / 2));
			sprite->Move(dropStartTime, dropEndTime, sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
		}
		dropTotalTime = dropTotalTime * (2.0f - acceler8);
		dropStartTime += dropTotalTime;
		dropEndTime = dropStartTime + dropTotalTime;
	}
}