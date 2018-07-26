#pragma once

#include "Sprite.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include <vector>

typedef struct raindrop {
	Sprite *sprite;
	Vector3 position;
	float size;
} raindrop;

class Walker {
public:
	//field of view
	float fov = 90;
	
	//current angle of walker
	Vector2 angle = Vector2::Zero;

	//current position of walker
	Vector3 position;

	std::vector<raindrop> raindrops;

	Walker(std::vector<Sprite *> sprites);

	void walk(float distance, Time startTime, Time endTime);

private:
	//check if the given 3d coordinate is on screen
	bool checkInScreen(Vector3 coordinates, float size);

	//convert 2d to 3d
	Vector3 twoToThree(Sprite *sprite);

	//convert 3d to 2d
	Vector3 threeToTwo(Vector3 coordinates);

	Vector2 findCollision(Vector2 a, Vector2 b);

	//add more sprites for walking
	void addSprites(float distance, Time startTime, Time endTime);

	//the maximum distance that any sprite will be drawn
	float max_distance = 30;

	//the minimum distance that a sprite will be drawn
	float min_distance = 1;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	const float minScale = 0.1;
	const float maxScale = 0.7;

	//sizes of the raindrop
	const float minSize = 0.1;
	const float maxSize = 1;
};
