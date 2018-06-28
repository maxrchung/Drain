#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include <cmath>

RainGenerator::RainGenerator(int rainCount, int dropCount, Time startTime, Time endTime, float acceleration) 
	: rainCount { rainCount }, dropCount { dropCount }, startTime { startTime }, endTime { endTime }, acceleration { acceleration },
	leftOfScreen{ -Vector2::ScreenSize.x / 2 }, totalTime{ endTime.ms - startTime.ms }, rainSpacing{ Vector2::ScreenSize.x / (rainCount - 1) } {
	//Parameter Big think: count, time start, time end, density(of a row of rain) angle, speed, acceleration, dropcount?
	//acceleration: raindrop accelerates after the current one finishes dropping
	//Note: acceleration only supports 0-2

	//Todo: randomize sprite size, rain position, rain tilt


	//Initiate drop time values
	dropTotalTime = totalTime / dropCount;
	dropStartTime = startTime.ms;
	dropEndTime = dropStartTime + dropTotalTime;

	while (dropEndTime < endTime.ms) {
		DrawRain();
	}
}

//Generates rain sprites and moves them
void RainGenerator::DrawRain() {
	for (int i = 0; i < rainCount; i++) {
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(leftOfScreen + i * rainSpacing, Vector2::ScreenSize.y / 2));
		sprite->Move(dropStartTime, dropEndTime, sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
	}

	VelocityController();

	//Increments time after row of rain is finished falling
	dropStartTime += dropTotalTime;
	dropEndTime = dropStartTime + dropTotalTime;
}

//Modifies the velocity of raindrops by changing time a raindrop takes to fall
void RainGenerator::VelocityController() {
	if (dropTotalTime >= minDropTime) { //Ensures rain doesn't fall faster than minDropTime
		dropTotalTime *= (2.0f - acceleration);
	}
}




