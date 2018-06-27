#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"

RainGenerator::RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime) {
	//Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration, dropcount?

	int leftOfScreen = -Vector2::ScreenSize.x / 2;
	int rainSpacing = Vector2::ScreenSize.x / (rainCount-1);
	int totalTime = endTime.ms - startTime.ms;
	int endDrop = totalTime / dropCount;

	int speed = 1000;

	for (int rainRow = 0; rainRow < dropCount; rainRow++) {
		for (int i = 0; i < rainCount; i++) {
			Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(leftOfScreen + i * rainSpacing, Vector2::ScreenSize.y / 2));
			sprite->Move(startTime.ms + (endDrop * rainRow) , startTime.ms + (endDrop * (rainRow + 1)) , sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
		}
	}
}