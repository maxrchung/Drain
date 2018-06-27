#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"

RainGenerator::RainGenerator(int rainCount) {
	//Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration?

	int leftOfScreen = -Vector2::ScreenSize.x / 2;

	int rainSpacing = Vector2::ScreenSize.x / (rainCount-1);

	int startTime, endTime;

	int speed;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < rainCount; i++) {
			Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(leftOfScreen + i * rainSpacing, Vector2::ScreenSize.y / 2));
			sprite->Move(0, 1000, sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
		}
	}
}